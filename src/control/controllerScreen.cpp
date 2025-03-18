//Includes
#include "../src/control/controllerScreen.hpp"
#include "../src/globals.hpp"
#include "../src/control/movement.hpp"
#include <string>
#include <queue>

//Number of iterations on the controller update loop
int loopCount = 0;

//Stores each line of the screen to be displayed and vibration
std::string lineone;
std::string linetwo;
std::string linethree;
std::string controllerRumble;

//List of overheating motors
std::vector<std::string> overheatingMotorsList;

//Format for a controller popup warning
struct controllerWarning {
    std::string line1;
    std::string line2;
    std::string vibration;
    int duration;
};

//List of current errors
std::queue<controllerWarning> currentControllerWarnings;


//This function should be run by opcontrol as part of its loop.
//Updates the controller text to match the line strings
void updateControllerScreen() {
    if (loopCount % 10 == 0) {master.clear(); updateLines();}
    else if (loopCount % 10 == 1) partner.clear();
    else if (loopCount % 10 == 2) master.set_text(0, 0, lineone);
    else if (loopCount % 10 == 3) partner.set_text(0, 0, lineone);
    else if (loopCount % 10 == 4) master.set_text(1, 0, linetwo);
    else if (loopCount % 10 == 5) partner.set_text(1, 0, linetwo);
    else if (loopCount % 10 == 6) master.set_text(2, 0, linethree);
    else if (loopCount % 10 == 7) partner.set_text(2, 0, linethree);
    else if (loopCount % 10 == 8) master.rumble(controllerRumble.c_str());
    else if (loopCount % 10 == 9) partner.rumble(controllerRumble.c_str());
    loopCount += 1;
}

//Function to update the line strings with any faults
void updateLines() {
    //Default line values
    lineone = "System OK";
    linetwo = "";
    linethree = "";
    controllerRumble = "";
    
    //Display any current warnings one by one
    if (currentControllerWarnings.size() > 0) {
        lineone = &" Warning " [ currentControllerWarnings.size()];
        linetwo = currentControllerWarnings.front().line1;
        linethree = currentControllerWarnings.front().line2;
        controllerRumble = currentControllerWarnings.front().vibration;
        currentControllerWarnings.front().vibration = "";
        currentControllerWarnings.front().duration --;
        if (currentControllerWarnings.front().duration == 0) currentControllerWarnings.pop();
        return; //Don't draw overheating motors on top of warnings
    }

    //Display any overheating motors if present 
    overheatingMotorsList = getOverheatingMotors();
    if (overheatingMotorsList.size() > 0) {
        lineone = " Motor Faults:";
        linetwo= "";
        for (std::string overheatingMotor : overheatingMotorsList) {
            if (linetwo.length() < 17) linetwo += overheatingMotor;
            else linethree += overheatingMotor;
        }
    }
}

//Checks the overheating status of each motor and adds the shorthand of
//any overheated motors to a list
std::vector<std::string> getOverheatingMotors() {
    std::vector<std::string> overheatingMotorsList;

    if (left_mtrs.is_over_temp_all().at(0)) overheatingMotorsList.push_back("LF ");
    if (left_mtrs.is_over_temp_all().at(1)) overheatingMotorsList.push_back("LM ");    
    if (left_mtrs.is_over_temp_all().at(2)) overheatingMotorsList.push_back("LB ");
    if (right_mtrs.is_over_temp_all().at(0)) overheatingMotorsList.push_back("RF ");    
    if (right_mtrs.is_over_temp_all().at(1)) overheatingMotorsList.push_back("RM ");
    if (right_mtrs.is_over_temp_all().at(2)) overheatingMotorsList.push_back("RB ");
    if (intake_top_mtr.is_over_temp()) overheatingMotorsList.push_back("iT ");
    if (intake_bot_mtr.is_over_temp()) overheatingMotorsList.push_back("iB ");
    
    return overheatingMotorsList;
}

//Function to add a controller warning to the list to be displayed
void raiseControllerWarning(std::string line1, std::string line2, std::string vibration, int duration) {
    currentControllerWarnings.push({line1, line2, vibration, duration});
}
//Also a simple version that only needs one input
void raiseControllerWarning(std::string errorText) {
    currentControllerWarnings.push({errorText, "", "..", 3});
}
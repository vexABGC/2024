#include "main.h"
#include "../src/globals.hpp"
#include "../src/control/movement.hpp"
#include <string>

// Number of iterations on the controller update loop
int loopCount = 0;

// Stores each line of the screen to be displayed
std::string lineone;
std::string linetwo;
std::string linethree;

// This function should be run by opcontrol as part of its loop.
// Updates the controller text to match the line strings
void updateControllerScreen() {
    if (loopCount % 80 == 0) master.clear();
    else if (loopCount % 80 == 1) partner.clear();
    else if (loopCount % 8 == 2) master.set_text(0, 0, lineone);
    else if (loopCount % 8 == 3) partner.set_text(0, 0, lineone);
    else if (loopCount % 8 == 4) master.set_text(1, 0, linetwo);
    else if (loopCount % 8 == 5) partner.set_text(1, 0, linetwo);
    else if (loopCount % 8 == 6) master.set_text(2, 0, linethree);
    else if (loopCount % 8 == 7) partner.set_text(2, 0, linethree);
}

// Function to update the line strings with the overheating motors
void updateLines() {
    std::vector<std::string> overheatingMotorsList = getOverheatingMotors();
    if (overheatingMotorsList.size() > 0) {
        for (std::string overheatingMotor : overheatingMotorsList) {
            // TODO: #2 Add line wrapping
            lineone += overheatingMotor;
        }
    }
}

// Checks the overheating status of each motor and adds the shorthand of
// any overheated motors to a list
std::vector<std::string> getOverheatingMotors() {
    std::vector<std::string> overheatingMotorsList;
    if (lf_mtr.is_over_temp()) overheatingMotorsList.push_back("LF ");
    if (lm_mtr.is_over_temp()) overheatingMotorsList.push_back("LM ");    
    if (lb_mtr.is_over_temp()) overheatingMotorsList.push_back("LB ");
    if (rf_mtr.is_over_temp()) overheatingMotorsList.push_back("RF ");    
    if (rm_mtr.is_over_temp()) overheatingMotorsList.push_back("RM ");
    if (rb_mtr.is_over_temp()) overheatingMotorsList.push_back("RB ");
    if (intake_top_mtr.is_over_temp()) overheatingMotorsList.push_back("iT");
    if (intake_bot_mtr.is_over_temp()) overheatingMotorsList.push_back("iB");
    // TODO: #3 Finish adding an overheat check for each motor
    return overheatingMotorsList;
}
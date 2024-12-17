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

//
std::vector<std::string> getOverheatingMotors() {
    std::vector<std::string> overheatingMotorsList;
    if (lf_mtr.is_over_temp()) overheatingMotorsList.push_back("LF");
    // TODO: #3 Finish adding an overheat check for each motor
    return overheatingMotorsList;
}
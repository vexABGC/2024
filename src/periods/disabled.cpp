//Includes
#include "main.h" // IWYU pragma: keep
#include "../src/control/controllerScreen.hpp"
#include "../src/control/movement.hpp"
#include "../src/globals.hpp"

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
    //End movement
    int inputs[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    movement(inputs);

    //Force disable intake
    intakeDirection = 0;

    //Update lines
    pros::delay(100);
    master.clear();
    while (true){
        updateControllerScreen();
        pros::delay(50);
    }
}
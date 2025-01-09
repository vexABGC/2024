//Includes
#include "main.h"
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

    //Force reenable intake
    intakeDirection = 1;
}
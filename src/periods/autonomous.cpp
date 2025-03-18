//Includes
#include "main.h"
#include "../src/globals.hpp"
#include "../src/autons/autons.hpp"

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
    //Intake off, and mogo up
    mogo_piston.set_value(0);
    pros::delay(100);

    //Auton select
    if (autonomousSelected == 0){
        //Left red
        leftRed();
    }
    else if (autonomousSelected == 1){
        //Right blue
        rightBlue();
    }
    else if (autonomousSelected == 2){
        //Right red
        rightRed();
    }
    else if (autonomousSelected == 3){
        //Left  blue
        leftBlue();
    }
    else if (autonomousSelected == 4){
        //Skills
        skills();
    }
    else if (autonomousSelected == 5){
        //Replay
        replay();
    }
    else {
        //Disabled auton
        master.rumble(".-.-");
    }
}
//Includes
#include "main.h"
#include "../src/globals.hpp"
#include "../src/control/movement.hpp"
#include <fstream>

//Methods
double toInch(double mm){
    return mm/25.4;
}

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
    intakeDirection = -2;
    mogo_piston.set_value(0);
    pros::delay(100);

    //Auton select
    if (autonomousSelected == 0){
        //Left red
        chassis.setPose(toInch(-135), toInch(-105), 180);

        //Rewind intake, and move up lady brown
        lady_brown_mtr.move_absolute(50 * LADY_BROWN_RATIO, 100);
        intake_top_mtr.move_relative(-320, 200);

        //Grab mogo
        chassis.moveToPose(0, toInch(600), 225, 3000, {.forwards = false}, false);
        mogo_piston.extend();

        //Dump preload, and grab 1st ring
        chassis.turnToHeading(270, 3000);
        intakeDirection = 1;
        chassis.moveToPoint(-toInch(400), toInch(600), 3000, {.forwards = true}, false);

        //Grab 2nd and 3rd rings
        chassis.moveToPoint(-toInch(550), toInch(900), 3000, {.forwards = true}, false);
        chassis.moveToPoint(-toInch(650), toInch(900), 3000, {.forwards = true}, false);

        //Touch ladder
        chassis.moveToPoint(0,toInch(600), 3000, {.forwards = false}, false);
        chassis.turnToPoint(toInch(800), toInch(800), 3000, {.forwards = true}, false);
        chassis.moveToPoint(toInch(800),toInch(800), 3000, {.forwards = true}, false);
    }
    else if (autonomousSelected == 1){
        //Right blue
        chassis.setPose(toInch(135), toInch(-105), 180);

        //Rewind intake, and move up lady brown
        lady_brown_mtr.move_absolute(40 * LADY_BROWN_RATIO, 100);
        intake_top_mtr.move_relative(-320, 200 * INTAKE_TOP_MULTIPLIER);

        //Grab mogo
        chassis.moveToPose(0, toInch(600), 225, 3000, {.forwards = false}, false);
        mogo_piston.extend();

        //Dump preload, and grab 1st ring
        chassis.turnToHeading(90, 3000);
        intakeDirection = 1;
        chassis.moveToPoint(toInch(400), toInch(600), 3000, {.forwards = true}, false);

        //Grab 2nd and 3rd rings
        chassis.moveToPoint(toInch(550), toInch(900), 3000, {.forwards = true}, false);
        chassis.moveToPoint(toInch(650), toInch(900), 3000, {.forwards = true}, false);

        //Touch ladder
        chassis.moveToPoint(0,toInch(600), 3000, {.forwards = false}, false);
        chassis.turnToPoint(-toInch(800), toInch(800), 3000, {.forwards = true}, false);
        chassis.moveToPoint(-toInch(800),toInch(800), 3000, {.forwards = true}, false);
    }
    else if (autonomousSelected == 2){
        //Right red
        chassis.setPose(toInch(135), toInch(-105), 180);

        //Rewind intake, and move up lady brown
        lady_brown_mtr.move_absolute(40 * LADY_BROWN_RATIO, 100);
        intake_top_mtr.move_relative(-320, 200 * INTAKE_TOP_MULTIPLIER);

        //Grab mogo
        chassis.moveToPose(0, toInch(600), 225, 3000, {.forwards = false}, false);
        mogo_piston.extend();

        //Dump preload, and grab 1st ring
        chassis.turnToHeading(90, 3000);
        intakeDirection = 1;
        chassis.moveToPoint(toInch(400), toInch(600), 3000, {.forwards = true}, false);
    }
    else if (autonomousSelected == 3){
        //Left blue
        chassis.setPose(toInch(-135), toInch(-105), 180);

        //Rewind intake, and move up lady brown
        lady_brown_mtr.move_absolute(50 * LADY_BROWN_RATIO, 100);
        intake_top_mtr.move_relative(-320, 200);

        //Grab mogo
        chassis.moveToPose(0, toInch(600), 225, 3000, {.forwards = false}, false);
        mogo_piston.extend();

        //Dump preload, and grab 1st ring
        chassis.turnToHeading(270, 3000);
        intakeDirection = 1;
        chassis.moveToPoint(-toInch(400), toInch(600), 3000, {.forwards = true}, false);
    }
    else if (autonomousSelected == 4){
        //Skills
        chassis.setPose(3, 0, 180);

        //Rewind intake, and move up lady brown
        lady_brown_mtr.move_absolute(40 * LADY_BROWN_RATIO, 100);
        intake_top_mtr.move_relative(-320, 200 * INTAKE_TOP_MULTIPLIER);

        //Mogo, turn, and score preload
        chassis.moveToPose(0, toInch(500), 180, 3000, {.forwards = false}, false);
        mogo_piston.extend();
        pros::delay(300);
        intakeDirection = 1;
        intake_bot_mtr.move(60);
        chassis.turnToHeading(0, 5000, {}, false);
        
        //Rings 1 - 4
        chassis.moveToPoint(0, toInch(1250), 5000, {.forwards = true}, false); //Ring 1 & 2
        chassis.moveToPoint(0, toInch(1100), 5000, {.forwards = false}, false); //Backwards
        chassis.turnToPoint(toInch(-600), toInch(1200), 5000, {.forwards=true}, false); //Rotate
        chassis.moveToPoint(toInch(-600), toInch(1200), 5000, {.forwards = true}, false); //Ring 3
        chassis.moveToPoint(toInch(-1050), toInch(1350), 5000, {.forwards = true}, false); //Ring 4

        //Corner
        chassis.moveToPoint(0, toInch(1100), 5000, {.forwards = false}, false); //Backwards to line up
        chassis.turnToPoint(toInch(800), toInch(1800), 5000, {.forwards = false}, false); //Rotate
        chassis.moveToPoint(toInch(800), toInch(1800), 5000, {.forwards = false}, false); //Corner final
    }
    else if (autonomousSelected == 5){
        //Replay
        //Load file
        std::ifstream file("/usd/sigma.auton", std::ios::binary);

        //Iterate through inputs
        for (int i = 0; i < INPUT_COUNT; i++){
            //Load bytes
            int inputs[14];
            char byte;
            for (int i = 0; i < 14; i++){
                file.read(&byte, 1);
                inputs[i] = int8_t(byte);
            }

            //Pass and delay
            movement(inputs);
            pros::delay(50);
        }

        //End movement
        int inputs[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        movement(inputs);
    }
    else {
        //Disabled auton
        master.rumble(".-.-");
    }
}
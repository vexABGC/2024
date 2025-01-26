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
    intakeDirection = 0;
    mogo_piston.set_value(0);

    //Auton select
    if (autonomousSelected == 0){
        //Left red
        chassis.setPose(toInch(-135), toInch(-105), 180);

        //Rewind intake, and move up lady brown
        lady_brown_mtr.move_absolute(40 * LADY_BROWN_RATIO, 100);
        intakeDirection = -2;
        pros::delay(300);
        intakeDirection = 0;

        //Mogo
        chassis.moveToPoint(toInch(0), toInch(300), 2000, {.forwards = false, .maxSpeed = 50, .minSpeed = 20});
        chassis.turnToHeading(-150, 2000, {.maxSpeed = 40, .minSpeed = 20});
        chassis.moveToPoint(toInch(200), toInch(800), 2000, {.forwards = false, .maxSpeed = 50}, false);
        mogo_piston.extend();
        pros::delay(500);

        //Put pre load on
        intakeDirection = 1;
    }
    else if (autonomousSelected == 1){
        //Right blue
        chassis.setPose(toInch(135), toInch(-105), 180);

        //Rewind intake, and move up lady brown
        lady_brown_mtr.move_absolute(40 * LADY_BROWN_RATIO, 100);
        intakeDirection = -2;
        pros::delay(300);
        intakeDirection = 0;

        //Mogo
        chassis.moveToPoint(toInch(0), toInch(300), 2000, {.forwards = false, .maxSpeed = 50, .minSpeed = 20});
        chassis.turnToHeading(150, 2000, {.maxSpeed = 40, .minSpeed = 20});
        chassis.moveToPoint(toInch(-200), toInch(800), 2000, {.forwards = false, .maxSpeed = 50}, false);
        mogo_piston.extend();
        chassis.moveToPoint(toInch(0), toInch(600), 2000, {.forwards = true, .maxSpeed = 50}, false);
        pros::delay(500);

        //Put pre load on, and grab 2nd ring
        intakeDirection = 1;
        chassis.moveToPose(toInch(500), toInch(600), 90, 2000, {.forwards = true, .maxSpeed = 50});
    }
    else if (autonomousSelected == 2){
        //Right red
        chassis.setPose(toInch(135), toInch(-105), 180);

        //Rewind intake, and move up lady brown
        lady_brown_mtr.move_absolute(40 * LADY_BROWN_RATIO, 100);
        intakeDirection = -2;
        pros::delay(300);
        intakeDirection = 0;

        //Mogo
        chassis.moveToPoint(toInch(0), toInch(300), 2000, {.forwards = false, .maxSpeed = 50, .minSpeed = 20}, false);
        chassis.moveToPoint(toInch(-200), toInch(800), 2000, {.forwards = false, .maxSpeed = 50}, false);
        mogo_piston.extend();
        chassis.moveToPoint(toInch(0), toInch(600), 2000, {.forwards = true, .maxSpeed = 50}, false);
        pros::delay(500);

        //Put pre load on, and grab 2nd ring
        intakeDirection = 1;
        chassis.moveToPose(toInch(500), toInch(600), 90, 2000, {.forwards = true, .maxSpeed = 50}, false);
    }
    else if (autonomousSelected == 3){
        //Left blue
        chassis.setPose(toInch(-135), toInch(-105), 180);

        //Rewind intake, and move up lady brown
        lady_brown_mtr.move_absolute(40 * LADY_BROWN_RATIO, 100);
        intakeDirection = -2;
        pros::delay(300);
        intakeDirection = 0;

        //Mogo
        chassis.moveToPoint(-toInch(0), toInch(300), 2000, {.forwards = false, .maxSpeed = 50, .minSpeed = 20}, false);
        chassis.moveToPoint(-toInch(-200), toInch(800), 2000, {.forwards = false, .maxSpeed = 50}, false);
        mogo_piston.extend();
        chassis.moveToPoint(-toInch(0), toInch(600), 2000, {.forwards = true, .maxSpeed = 50}, false);
        pros::delay(500);

        //Put pre load on, and grab 2nd ring
        intakeDirection = 1;
        chassis.moveToPose(-toInch(500), toInch(500), 90, 2000, {.forwards = true, .maxSpeed = 50}, false);
    }
    else if (autonomousSelected == 4){
        //Skills
        chassis.setPose(3, 0, 180);

        //Rewind intake, and move up lady brown
        lady_brown_mtr.move_absolute(40 * LADY_BROWN_RATIO, 100);
        intakeDirection = -2;
        pros::delay(700);
        intakeDirection = 0;

        //Mogo, turn, and score preload
        chassis.moveToPose(0, toInch(500), 180, 3000, {.forwards = false, .maxSpeed = 50}, false);
        mogo_piston.extend();
        pros::delay(300);
        intakeDirection = 1;
        intake_bot_mtr.move(60);
        chassis.turnToHeading(0, 5000, {.maxSpeed = 40}, false);
        
        //Rings 1 - 4
        chassis.moveToPoint(0, toInch(1250), 5000, {.forwards = true, .maxSpeed = 30}, false); //Ring 1 & 2
        chassis.moveToPoint(0, toInch(1100), 5000, {.forwards = false, .maxSpeed = 50}, false); //Backwards
        chassis.turnToPoint(toInch(-600), toInch(1200), 5000, {.forwards=true, .maxSpeed = 30}, false); //Rotate
        chassis.moveToPoint(toInch(-600), toInch(1200), 5000, {.forwards = true, .maxSpeed = 50}, false); //Ring 3
        chassis.moveToPoint(toInch(-1050), toInch(1350), 5000, {.forwards = true, .maxSpeed = 50}, false); //Ring 4

        //Corner
        chassis.moveToPoint(0, toInch(1100), 5000, {.forwards = false, .maxSpeed = 50}, false); //Backwards to line up
        chassis.turnToPoint(toInch(800), toInch(1800), 5000, {.forwards = false, .maxSpeed = 30}, false); //Rotate
        chassis.moveToPoint(toInch(800), toInch(1800), 5000, {.forwards = false, .maxSpeed = 80}, false); //Corner final
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
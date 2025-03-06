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
        ladyBrownAngle = 50 * LADY_BROWN_RATIO;
        intake_top_mtr.move_relative(-320, 200);

        //Grab mogo
        chassis.moveToPoint(toInch(270), toInch(670), 3000, {.forwards = false, .maxSpeed=80}, false);
        mogo_piston.extend();
        pros::delay(200);

        //Dump preload, and grab 1st ring
        chassis.turnToHeading(270, 3000);
        chassis.moveToPoint(-toInch(400), toInch(600), 3000, {.forwards = true}, true);
        pros::delay(100);
        intakeDirection = 1;
        intake_bot_mtr.move(60);

        //Touch ladder
        chassis.moveToPoint(0,toInch(600), 3000, {.forwards = false}, false);
        chassis.turnToPoint(toInch(800), toInch(800), 3000, {.forwards = true}, false);
        chassis.moveToPoint(toInch(800),toInch(800), 3000, {.forwards = true}, false);
    }
    else if (autonomousSelected == 1){
        //Right blue
        chassis.setPose(toInch(135), toInch(-105), 180);

        //Rewind intake, and move up lady brown
        lady_brown_mtr.move_absolute(50 * LADY_BROWN_RATIO, 100);
        ladyBrownAngle = 50 * LADY_BROWN_RATIO;
        intake_top_mtr.move_relative(-320, 200);

        //Grab mogo
        chassis.moveToPoint(-toInch(270), toInch(670), 3000, {.forwards = false, .maxSpeed=80}, false);
        mogo_piston.extend();
        pros::delay(200);

        //Dump preload, and grab 1st ring
        chassis.turnToHeading(90, 3000, {}, false);
        chassis.moveToPoint(toInch(400), toInch(550), 3000, {.forwards = true}, true);
        pros::delay(100);
        intakeDirection = 1;
        intake_bot_mtr.move(60);

        //Touch ladder
        chassis.moveToPoint(0,toInch(600), 3000, {.forwards = false}, false);
        chassis.turnToPoint(-toInch(800), toInch(800), 3000, {.forwards = true}, false);
        chassis.moveToPoint(-toInch(800),toInch(800), 3000, {.forwards = true}, false);
    }
    else if (autonomousSelected == 2){
        //Right red
        chassis.setPose(toInch(135), toInch(-105), 180);

        //Rewind intake, and move up lady brown
        lady_brown_mtr.move_absolute(50 * LADY_BROWN_RATIO, 100);
        ladyBrownAngle = 50 * LADY_BROWN_RATIO;
        intake_top_mtr.move_relative(-320, 200);

        //Grab mogo
        chassis.moveToPoint(-toInch(270), toInch(670), 3000, {.forwards = false, .maxSpeed=80}, false);
        mogo_piston.extend();
        pros::delay(200);

        //Dump preload, and grab 1st ring
        chassis.turnToHeading(90, 3000, {}, false);
        chassis.moveToPoint(toInch(400), toInch(550), 3000, {.forwards = true}, true);
        pros::delay(100);
        intakeDirection = 1;
        intake_bot_mtr.move(60);

        //Touch ladder
        chassis.moveToPoint(0,toInch(600), 3000, {.forwards = false}, false);
        chassis.turnToPoint(-toInch(800), toInch(800), 3000, {.forwards = true}, false);
        chassis.moveToPoint(-toInch(800),toInch(800), 3000, {.forwards = true}, false);
    }
    else if (autonomousSelected == 3){
        //Left blue
        chassis.setPose(toInch(-135), toInch(-105), 180);

        //Rewind intake, and move up lady brown
        lady_brown_mtr.move_absolute(50 * LADY_BROWN_RATIO, 100);
        ladyBrownAngle = 50 * LADY_BROWN_RATIO;
        intake_top_mtr.move_relative(-320, 200);

        //Grab mogo
        chassis.moveToPoint(toInch(270), toInch(670), 3000, {.forwards = false, .maxSpeed=80}, false);
        mogo_piston.extend();
        pros::delay(200);

        //Dump preload, and grab 1st ring
        chassis.turnToHeading(270, 3000);
        chassis.moveToPoint(-toInch(400), toInch(600), 3000, {.forwards = true}, true);
        pros::delay(100);
        intakeDirection = 1;
        intake_bot_mtr.move(60);

        //Touch ladder
        chassis.moveToPoint(0,toInch(600), 3000, {.forwards = false}, false);
        chassis.turnToPoint(toInch(800), toInch(800), 3000, {.forwards = true}, false);
        chassis.moveToPoint(toInch(800),toInch(800), 3000, {.forwards = true}, false);
    }
    else if (autonomousSelected == 4){
        //Skills
        chassis.setPose(0, toInch(-1525), 270);

        //Rewind intake, and move up lady brown
        lady_brown_mtr.move_absolute(40 * LADY_BROWN_RATIO, 100);
        intake_top_mtr.move_relative(-320, 200 * INTAKE_TOP_MULTIPLIER);
        pros::delay(700);

        //Score preload on alliance stake
        intakeDirection = 1;
        pros::delay(700);

        //Grab mogo 1
        chassis.moveToPoint(toInch(-1200), 0, 2000);
        chassis.moveToPoint(toInch(-1200), toInch(-600), 2000);

        //Rings 1 - 5
        chassis.moveToPoint(toInch(-600), toInch(-600), 2000);
        chassis.moveToPoint(toInch(-72), toInch(-1382), 2000);
        chassis.moveToPoint(toInch(-200), toInch(-1200), 2000);
        chassis.moveToPoint(toInch(-1440), toInch(-1200), 2000);

        //Put mogo 1 in corner and move out
        chassis.moveToPoint(toInch(-1200), toInch(-1200), 2000);
        chassis.moveToPoint(toInch(-1450), toInch(-1450), 2000);
        chassis.moveToPoint(toInch(-1200), toInch(-1200), 2000);

        //Grab mogo 2
        chassis.moveToPoint(toInch(-1200), 0, 2000);
        chassis.moveToPoint(toInch(-1200), toInch(600), 2000);

        //Rings 6 - 10
        chassis.moveToPoint(toInch(-600), toInch(600), 2000);
        chassis.moveToPoint(toInch(-72), toInch(1382), 2000);
        chassis.moveToPoint(toInch(-200), toInch(1200), 2000);
        chassis.moveToPoint(toInch(-1440), toInch(1200), 2000);

        //Put mogo 2 in corner and move out
        chassis.moveToPoint(-47.244, 47.244, 2000);
        chassis.moveToPoint(-57.087, 57.087, 2000);
        chassis.moveToPoint(-47.244, 47.244, 2000);
        chassis.moveToPoint(38.482, 34.346, 2000);
        chassis.moveToPoint(47.244, 0, 2000);
        chassis.moveToPoint(58.939, 17.765, 2000);
        chassis.moveToPoint(60.447, 52.435, 2000);
        chassis.moveToPoint(58.078, -17.767, 2000);
        chassis.moveToPoint(60.231, -53.729, 2000);
        chassis.moveToPoint(53.986, -24.442, 2000);
        chassis.moveToPoint(23.623, -23.581, 2000);
        chassis.moveToPoint(23.623, -47.053, 2000);
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
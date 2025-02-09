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
        chassis.setPose(0, toInch(-325), 0);

        //Rewind intake, and move up lady brown
        lady_brown_mtr.move_absolute(40 * LADY_BROWN_RATIO, 100);
        intake_top_mtr.move_relative(-320, 200 * INTAKE_TOP_MULTIPLIER);
        pros::delay(700);

        //Score preload on alliance stake
        intakeDirection = 1;
        pros::delay(700);

        //Grab mogo and face rings
        chassis.moveToPoint(0, 0, 3000, {.forwards = true}, false);
        chassis.turnToHeading(-90, 3000, {}, false);
        chassis.moveToPoint(toInch(500), 0, 3000, {.forwards = false}, false);
        mogo_piston.extend();
        pros::delay(300);
        intakeDirection = 1;
        intake_bot_mtr.move(60);
        chassis.turnToHeading(90, 3000, {}, false);
        
        //Rings 1 - 4
        chassis.moveToPoint(toInch(1300), 0, 3000, {.forwards = true}, false); //Ring 1
        chassis.moveToPoint(toInch(1100), 0, 1000, {.forwards = false}, false); //Backwards
        chassis.moveToPoint(toInch(1450), 0, 1000, {.forwards = true}, false); //Ring 2
        chassis.moveToPoint(toInch(1100), 0, 1000, {.forwards = false}, false); //Backwards
        chassis.turnToPoint(toInch(1200), toInch(600), 1000, {.forwards=true}, false); //Rotate
        chassis.moveToPoint(toInch(1200), toInch(600), 2000, {.forwards = true}, false); //Ring 3
        chassis.turnToPoint(toInch(600), toInch(600), 1000, {.forwards=true}, false); //Rotate
        chassis.moveToPoint(toInch(600), toInch(600), 2000, {.forwards = true}, false); //Ring 4

        //Corner 1
        chassis.turnToPoint(toInch(1600), toInch(-400), 1000, {.forwards = false}, false);
        chassis.moveToPoint(toInch(1600), toInch(-400), 3000, {.forwards = false}, false);
        mogo_piston.retract(); //Dump mogo
        pros::delay(700);
        chassis.moveToPoint(toInch(1200), toInch(0), 3000, {.forwards = true}, false); //Drive out of corner
        chassis.turnToPoint(toInch(-500), 0, 1500, {.forwards = false}, false);

        //Grab mobile goal
        chassis.moveToPoint(toInch(-500), 0, 3000, {.forwards = false}, false);
        mogo_piston.extend();
        pros::delay(300);
        intakeDirection = 1;
        intake_bot_mtr.move(60);
        chassis.turnToHeading(90, 3000, {}, false);

        //Rigns 5 - 8
        chassis.moveToPoint(toInch(-1300), 0, 3000, {.forwards = true}, false); //Ring 1
        chassis.moveToPoint(toInch(-1100), 0, 1000, {.forwards = false}, false); //Backwards
        chassis.moveToPoint(toInch(-1450), 0, 1000, {.forwards = true}, false); //Ring 2
        chassis.moveToPoint(toInch(-1100), 0, 1000, {.forwards = false}, false); //Backwards
        chassis.turnToPoint(toInch(-1200), toInch(600), 1000, {.forwards=true}, false); //Rotate
        chassis.moveToPoint(toInch(-1200), toInch(600), 2000, {.forwards = true}, false); //Ring 3
        chassis.turnToPoint(toInch(-600), toInch(600), 1000, {.forwards=true}, false); //Rotate
        chassis.moveToPoint(toInch(-600), toInch(600), 2000, {.forwards = true}, false); //Ring 4

        //Corner 2
        chassis.turnToPoint(toInch(-1600), toInch(-400), 1000, {.forwards = false}, false);
        chassis.moveToPoint(toInch(-1600), toInch(-400), 3000, {.forwards = false}, false);
        mogo_piston.retract(); //Dump mogo
        pros::delay(700);
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
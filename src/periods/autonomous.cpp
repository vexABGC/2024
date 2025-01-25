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
        //Left red (tuning)
        chassis.setPose(0, 0 ,0);
        //chassis.turnToHeading(180, 2000, {.maxSpeed = 80}, false);
        chassis.moveToPoint(0, 23.622, 2000, {.forwards = true, .maxSpeed = 80}, false);
        pros::delay(5000);
        chassis.moveToPose(0, 0, 0, 2000, {.forwards = false, .maxSpeed = 40}, false);
    }
    else if (autonomousSelected == 1){
        //Right blue
        //Starting position, drop intake
        chassis.setPose(toInch(1200), toInch(900), 0);
        intakeDirection = -1;
        pros::delay(400);
        intakeDirection = 0;

        //Pick up mogo
        chassis.moveToPoint(toInch(900), toInch(900), 2000, {.forwards = false, .maxSpeed = 450}, false);
        chassis.turnToPoint(toInch(600), toInch(600), 2000, {.forwards = false, .maxSpeed = 450}, false);
        chassis.moveToPoint(toInch(600), toInch(600), 2000, {.forwards = false, .maxSpeed = 450}, false);
        mogo_piston.set_value(1);

        //Pick up first ring
        chassis.turnToPoint(toInch(600), toInch(100), 2000, {.forwards = true, .maxSpeed = 450}, false);
        intakeDirection = 1;
        intake_bot_mtr.move(0.7 * 127);
        chassis.moveToPoint(toInch(600), toInch(100), 2000, {.forwards = true, .maxSpeed = 450}, false);

        //Pick second/third rings
        chassis.turnToPoint(toInch(0) + 12.5, toInch(1200) - 12.5, 2000, {.forwards = true, .maxSpeed = 450}, false);
        chassis.moveToPoint(toInch(0) + 12.5, toInch(1200) - 12.5, 2000, {.forwards = true, .maxSpeed = 450}, false);
        chassis.moveToPoint(toInch(300), toInch(900), 2000, {.forwards = false, .maxSpeed = 450}, false);
        chassis.turnToPoint(toInch(0) + 12.5, toInch(1200) - 5.5, 2000, {.forwards = true, .maxSpeed = 450}, false);
        chassis.moveToPoint(toInch(0) + 12.5, toInch(1200) - 5.5, 2000, {.forwards = true, .maxSpeed = 450}, false);

        //Contact elevation bar
        chassis.moveToPoint(toInch(600), toInch(600), 2000, {.forwards = false, .maxSpeed=450}, false);
        chassis.turnToPoint(toInch(600), toInch(0), 2000, {.forwards = true, .maxSpeed=450}, false);
        intakeDirection = 0;
        chassis.moveToPoint(toInch(600), toInch(0) + 8, 2000, {.forwards = true, .maxSpeed=450}, false);
    }
    else if (autonomousSelected == 2){
        //Right red (demo)
        chassis.setPose(0, 0, 0);

        //Top left
        chassis.moveToPose(0,toInch(1200), 0,5000, {.forwards = true, .maxSpeed = 80});

        //Top right
        chassis.turnToPoint(toInch(2500), toInch(1200),5000, {.forwards = true, .maxSpeed = 40});
        chassis.moveToPoint(toInch(2500), toInch(1200),5000, {.forwards = true, .maxSpeed = 60});

        //Bottom right backwards
        chassis.turnToPoint(toInch(2500), 0,5000, {.forwards = true, .maxSpeed = 40});
        chassis.moveToPose(toInch(3250), 0, 0,5000, {.forwards = true, .maxSpeed = 60});

        //Top left backwards
        chassis.turnToPoint(0,toInch(1200),5000, {.forwards = false, .maxSpeed = 40});
        chassis.moveToPoint(0,toInch(1200),5000, {.forwards = false, .maxSpeed = 40});

        //Return to start pose (backwards)
        chassis.turnToPoint(0,0,5000, {.forwards = false, .maxSpeed = 40});
        chassis.moveToPose(0,0,0,5000, {.forwards = false, .maxSpeed = 40});
    }
    else if (autonomousSelected == 3){
        //Left blue
        //Starting position
        chassis.setPose(toInch(1200), toInch(-900), 0);

        //Pick up mogo
        chassis.moveToPoint(toInch(900), toInch(-900), 2000, {.forwards = false, .maxSpeed = 450}, false);
        chassis.turnToPoint(toInch(600), toInch(-600), 2000, {.forwards = false, .maxSpeed = 450}, false);
        chassis.moveToPoint(toInch(600), toInch(-600), 2000, {.forwards = false, .maxSpeed = 450}, false);
        mogo_piston.set_value(1);

        //Pick up first ring
        chassis.turnToPoint(toInch(600), toInch(-100), 2000, {.forwards = true, .maxSpeed = 450}, false);
        chassis.moveToPoint(toInch(600), toInch(-100), 2000, {.forwards = true, .maxSpeed = 450}, false);

        //Contact elevation bar
        chassis.turnToPoint(toInch(60), toInch(0), 2000, {.forwards = true, .maxSpeed=450}, false);
        chassis.moveToPoint(toInch(60), toInch(0) - 8, 2000, {.forwards = true, .maxSpeed=450}, false);
    }
    else if (autonomousSelected == 4){
        //Skills
        //Origin
        chassis.setPose(-62.2, 0, 180);
        intake_top_mtr.move(-127);
        pros::delay(300);
        intake_top_mtr.move(0);

        //Mogo 1
        chassis.moveToPose(-47.2, -23.6, -90, 2000, {.forwards=false, .maxSpeed=160});
        mogo_piston.set_value(1);
        intake_top_mtr.move(105);
        intake_bot_mtr.move(127);

        //First 5 rings to pick up
        chassis.moveToPoint(-30.6, -23.6, 2000, {.forwards=true, .maxSpeed=160}, false); //1 ring
        chassis.moveToPoint(-05.0, -54.0, 2000, {.forwards=true, .maxSpeed=160}, false); //1 ring
        chassis.moveToPoint(-18.6, -52.2, 2000, {.forwards=true, .maxSpeed=160}, false); //1 ring
        chassis.moveToPoint(-54, -47.8, 2000, {.forwards=true, .maxSpeed=160}, false); //2 rings

        //Deposit in corner
        chassis.moveToPoint(-47.8, -47.8, 2000, {.forwards=false, .maxSpeed=160}, false);
        intake_top_mtr.move(0);
        intake_bot_mtr.move(0);
        chassis.turnToPoint(-59, -59, 2000, {.forwards=false, .maxSpeed=160}, false);
        chassis.moveToPoint(-52, -52, 2000, {.forwards=false, .maxSpeed=160}, false);
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
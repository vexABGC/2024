//includes
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "main.h"
#include "../src/globals.hpp"
#include "../src/control/movement.hpp"
#include <fstream>

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
    //Auton select
    if (autonomousSelected == 0){
        //Left red (tuning)
        chassis.setPose(0, 0 ,0);
        chassis.turnToHeading(180, 1000, {.maxSpeed = 160}, false);
        chassis.moveToPoint(0, 23.622, 1000, {.forwards = true, .maxSpeed = 160}, false);
        return;
    }
    else if (autonomousSelected == 1){
        //Right blue (demo)
        chassis.setPose(0, 0, 0);
        //top left
        chassis.moveToPoint(0,47.244,5000, {.forwards = true, .maxSpeed = 400});

        //top right
        chassis.turnToPoint(118.11,47.244,5000, {.forwards = true, .maxSpeed = 400});
        chassis.moveToPoint(118.11,47.244,5000, {.forwards = true, .maxSpeed = 400});

        //bottom right backwards
        chassis.turnToPoint(118.11,0,5000, {.forwards = false, .maxSpeed = 400});
        chassis.moveToPoint(118.11,0,5000, {.forwards = false, .maxSpeed = 400});

        //top left backwards
        chassis.turnToPoint(0,47.244,5000, {.forwards = false, .maxSpeed = 400});
        chassis.moveToPoint(0,47.244,5000, {.forwards = false, .maxSpeed = 400});

        //return to start pose (backwards)
        chassis.turnToPoint(0,0,5000, {.forwards = false, .maxSpeed = 400});
        chassis.moveToPoint(0,0,5000, {.forwards = false, .maxSpeed = 400});
        chassis.turnToHeading(0,5000, {.maxSpeed = 400});
    }
    else if (autonomousSelected == 2){
        //Right red
    }
    else if (autonomousSelected == 3){
        //Left blue
    }
    else if (autonomousSelected == 4){
        //Skills
        //Origin
        chassis.setPose(-62.2, 0, 180);
        mogo_piston.set_value(0);
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
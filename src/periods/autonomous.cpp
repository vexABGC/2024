//Includes
#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include <sstream>
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
        chassis.setPose(toInch(-1580), toInch(0), 90);

        //Rewind intake, and move up lady brown
        lady_brown_mtr.move_absolute(40 * LADY_BROWN_RATIO, 100);
        intake_top_mtr.move_relative(-320, 200 * INTAKE_TOP_MULTIPLIER);
        pros::delay(400);

        //Score preload on alliance stake
        intakeDirection = 1;
        pros::delay(800);
        intake_bot_mtr.move(127);

        //Grab mogo 1
        chassis.moveToPoint(toInch(-1200), 0, 2000, {.forwards = true}, false);
        chassis.turnToPoint(toInch(-1200), toInch(-600), 2000,  {.forwards = false}, false);
        chassis.moveToPoint(toInch(-1200), toInch(-600), 2000,  {.forwards = false}, false);
        mogo_piston.extend();
        pros::delay(300);

        //Rings 1 - 5
        chassis.turnToPoint(toInch(-600), toInch(-600), 2000,   {.forwards = true, .maxSpeed = 70}, false);
        chassis.moveToPoint(toInch(-600), toInch(-600), 2000,   {.forwards = true, .maxSpeed = 70, .minSpeed = 50}, false);
        chassis.turnToPoint(toInch(-100), toInch(-1250), 2000,   {.forwards = true, .maxSpeed = 70, .minSpeed = 50}, false);
        chassis.moveToPoint(toInch(-100), toInch(-1250), 2000,   {.forwards = true, .maxSpeed = 70, .minSpeed = 50}, false);
        chassis.turnToPoint(toInch(-600), toInch(-1200), 2000,   {.forwards = true, .maxSpeed = 70, .minSpeed = 50}, false);
        chassis.moveToPoint(toInch(-600), toInch(-1200), 3000,   {.forwards = true, .maxSpeed = 70, .minSpeed = 50}, false);
        chassis.turnToPoint(toInch(-1540), toInch(-1200), 2000,   {.forwards = true, .maxSpeed = 70, .minSpeed = 50}, false);
        chassis.moveToPoint(toInch(-1630), toInch(-1200), 3000,   {.forwards = true, .maxSpeed = 60, .minSpeed = 30}, false);
        pros::delay(500);

        //Put mogo 1 in corner and move out
        chassis.moveToPoint(toInch(-1200), toInch(-1200), 3000, {.forwards = true, .minSpeed = 40}, false);
        chassis.turnToPoint(toInch(-1750), toInch(-1600), 3000, {.forwards = false, .minSpeed = 40}, false);
        chassis.moveToPose(toInch(-2000), toInch(-1700), 45, 2000, {.forwards = false, .minSpeed = 70}, false);
        mogo_piston.retract();
        //std::stringstream out("X: ");
        //out << chassis.getPose().x << " Y: " << chassis.getPose().y << "A: " << chassis.getPose().theta;
        //master.set_text(0, 0, out.str());
        chassis.moveToPoint(toInch(-1200), toInch(-1200), 2000, {.forwards = true});

        //Grab mogo 2
        chassis.moveToPoint(toInch(-1200), 0, 2000, {.forwards = true}, false);
        chassis.turnToPoint(toInch(-1200), toInch(600), 2000,  {.forwards = false}, false);
        chassis.moveToPose(toInch(-1200), toInch(700), 180, 3000,  {.forwards = false}, false);
        mogo_piston.extend();
        pros::delay(300);

        //Rings 6 - 10
        chassis.turnToPoint(toInch(-600), toInch(600), 2000,   {.forwards = true, .maxSpeed = 70, .minSpeed = 50}, false);
        chassis.moveToPoint(toInch(-600), toInch(600), 2000,   {.forwards = true, .maxSpeed = 70, .minSpeed = 50}, false);
        chassis.turnToPoint(toInch(-72), toInch(1382), 2000,   {.forwards = true, .maxSpeed = 70, .minSpeed = 50}, false);
        chassis.moveToPoint(toInch(-40), toInch(1300), 2000,   {.forwards = true, .maxSpeed = 70, .minSpeed = 50}, false);
        chassis.turnToPoint(toInch(-600), toInch(1200), 2000,   {.forwards = true, .maxSpeed = 70, .minSpeed = 50}, false);
        chassis.moveToPoint(toInch(-600), toInch(1200), 3000,   {.forwards = true, .maxSpeed = 70, .minSpeed = 50}, false);
        chassis.turnToPoint(toInch(-1540), toInch(1250), 2000,   {.forwards = true, .maxSpeed = 70, .minSpeed = 50}, false);
        chassis.moveToPoint(toInch(-1540), toInch(1250), 3000,   {.forwards = true, .maxSpeed = 60, .minSpeed = 30}, false);
        pros::delay(500);

        //Put mogo 2 in corner and move out
        chassis.moveToPoint(toInch(-1200), toInch(1200), 3000, {.forwards = true, .minSpeed = 40}, false);
        chassis.turnToPoint(toInch(-1750), toInch(1600), 3000, {.forwards = false, .minSpeed = 40}, false);
        chassis.moveToPose(toInch(-2200), toInch(1700), 135, 2000, {.forwards = false, .minSpeed = 70}, false);
        mogo_piston.retract();
        pros::delay(300);
        intakeDirection = 0;
        chassis.moveToPoint(toInch(-1200), toInch(1200), 2000, {.forwards = true}, false);

        //Ring 11
        chassis.turnToPoint(toInch(-200), toInch(1200), 3000, {.forwards = true}, false);
        chassis.moveToPoint(toInch(-200), toInch(1200), 3000, {.forwards = true}, false);
        chassis.turnToPoint(toInch(400), toInch(600), 3000, {.forwards = true}, false);
        chassis.moveToPoint(toInch(400), toInch(600), 3000, {.forwards = true}, false);

        //Mogo 3
        chassis.turnToPoint(toInch(1000), toInch(0), 3000, {.forwards = false}, false);
        chassis.moveToPoint(toInch(1000), toInch(0), 3000, {.forwards = false}, false);
        mogo_piston.extend();
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
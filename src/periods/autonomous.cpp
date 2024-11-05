//includes
#include "main.h"
#include "../src/globals.hpp"
#include "../src/control/movement.hpp"
#include <fstream>
using namespace okapi;

//auton constants
#define INPUT_COUNT 300
#define PI 3.141592653589793
#define WHEEL_DIAMETER 4.125
#define WHEEL_TREAD 15.25
#define TURN_ERROR 300

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
    //Extend piston
    arm_piston.set_value(1);

    //Setup odom
    left_mtrs.move_velocity(0);
    right_mtrs.move_velocity(0);
    std::shared_ptr<OdomChassisController> chassis = ChassisControllerBuilder()
        //Green inserts, 4.125" omni wheels, 15" wheel track
        .withMotors({LF_PRT, LM_PRT, LB_PRT}, {RF_PRT, RM_PRT, RB_PRT})
        .withGains(
            {0.004, 0, 0.0003}, //Distance gain
            {0.001, 0, 0.0001}, //Turn gains
            {0.0003, 0, 0.0003}  //Angle gains
        )
        .withDimensions(AbstractMotor::gearset::blue, {{4_in, 15.125_in}, imev5GreenTPR})
        .buildOdometry();
    
    
    chassis->setState({0_in, 0_in, 0_deg});
    chassis->setMaxVelocity(100);

    //Auton select
    if (autonomousSelected == 0){
        //Left
        //start of auton
        //arm & piston up
        mogo_piston.set_value(1);
        arm_mtr.move(0.6 * 127);
        pros::delay(700);
        //move forward by amount
        chassis->moveDistance(-36.0_in);
        //turn by angle
        chassis->turnAngle(-90.0_deg);
        //move forward by amount
        chassis->moveDistance(-12.0_in);
        //turn by angle
        chassis->turnAngle(90.0_deg);
        //move forward by amount
        chassis->moveDistance(-12.0_in);
        //mogo mech
        mogo_piston.set_value(0);
        //move forward by amount
        chassis->moveDistance(12.0_in);
    }
    else if (autonomousSelected == 1){
        //Right
        //start of auton
        //arm & piston up
        mogo_piston.set_value(1);
        arm_mtr.move(0.6 * 127);
        pros::delay(700);
        //move forward by amount
        chassis->moveDistance(-36.0_in);
        //turn by angle
        chassis->turnAngle(90.0_deg);
        //move forward by amount
        chassis->moveDistance(-12.0_in);
        //turn by angle
        chassis->turnAngle(-90.0_deg);
        //move forward by amount
        chassis->moveDistance(-12.0_in);
        //mogo mech
        mogo_piston.set_value(0);
        //move forward by amount
        chassis->moveDistance(12.0_in);
    }
    else if (autonomousSelected == 2){
        //Skills
    }
    else if (autonomousSelected == 3){
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
        //Error
        master.rumble(".-.-");
    }
}
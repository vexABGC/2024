//includes
#include "main.h"
#include "../src/globals.hpp"

//local globals
double angleRadians = 0; //1.57079632679;
double deltaL = 0;
double lTrackPrev = 0;//l_rot.get_position();
double rTrackPrev = 0;//r_rot.get_position();

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
    //set brake mode on motors
    lf_mtr.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    lb_mtr.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    rf_mtr.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    rb_mtr.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    while (true){
        //take joystick input
        double leftJoyY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        double rightJoyX = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        //apply dead zones to joysticks
        leftJoyY = (abs(leftJoyY) < deadZone) ? 0 : leftJoyY;
        rightJoyX = (abs(rightJoyX) < deadZone) ? 0 : rightJoyX;

        //scale down inputs to 0 - 1
        leftJoyY /= 127;
        rightJoyX /= 127;

        //update motor when neither input is 0
        if (leftJoyY != 0 || rightJoyX != 0){
            left_mtrs.move_velocity((leftJoyY + rightJoyX) * maxDriveRPM);
            right_mtrs.move_velocity((leftJoyY - rightJoyX) * maxDriveRPM);
        }else{
            left_mtrs.brake();
            right_mtrs.brake();
        }
        
    }
}
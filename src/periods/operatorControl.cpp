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
        //take joystick input with dead zones
        int leftJoyX = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
        int leftJoyY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightJoyX = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        int rightJoyY = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

        //apply dead zones to joysticks
        leftJoyX = (abs(leftJoyX) < deadZone) ? 0 : leftJoyX;
        leftJoyY = (abs(leftJoyY) < deadZone) ? 0 : leftJoyY;
        rightJoyX = (abs(rightJoyX) < deadZone) ? 0 : rightJoyX;
        rightJoyY = (abs(rightJoyY) < deadZone) ? 0 : rightJoyY;

        //create drive, strafe, and turn desired values based on rotation
        double strafe = leftJoyX / 127;
        double drive = leftJoyY / 127;
        double turn = rightJoyX / 127;

        //create outputs with global strafe
        double lf_out = (drive + strafe + turn);
        double lb_out = (drive - strafe + turn);
        double rf_out = (drive - strafe - turn);
        double rb_out = (drive + strafe - turn);

        //fix scaling if output > 1
        int max = lf_out;
        if (max < lb_out) max = lb_out;
        if (max < rf_out) max = rf_out;
        if (max < rb_out) max = rb_out;
        if (max > 1){
            lf_out /= max;
            lb_out /= max;
            rf_out /= max;
            rb_out /= max;
        }

        //update motor velocity, if velocity = 0 then brake
        if (lf_out != 0 && lb_out != 0 && rf_out != 0 && rb_out != 0){
            lf_mtr.move_velocity(lf_out * maxDriveRPM);
            lb_mtr.move_velocity(lb_out * maxDriveRPM);
            rf_mtr.move_velocity(rf_out * maxDriveRPM);
            rb_mtr.move_velocity(rb_out * maxDriveRPM);
        }else{
            lf_mtr.brake();
            lb_mtr.brake();
            rf_mtr.brake();
            rb_mtr.brake();
        }
        
    }
}
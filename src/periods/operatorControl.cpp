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
    while (true){
        //take joystick input
        int leftJoyY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightJoyX = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        //apply dead zones to joysticks
        leftJoyY = (abs(leftJoyY) < DEAD_ZONE) ? 0 : leftJoyY;
        rightJoyX = (abs(rightJoyX) < DEAD_ZONE) ? 0 : rightJoyX;

        //update motors
        left_mtrs.move((leftJoyY + rightJoyX) * SPEED_MULTIPLIER);
        right_mtrs.move((leftJoyY - rightJoyX) * SPEED_MULTIPLIER);

        //pneumatics
        mogo_piston.set_value(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1));

        //intake
        intake_mtr.move(127 * (
            master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)
            - master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)
        ));

        pros::delay(20);     
    }
}
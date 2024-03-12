//includes
#include "main.h"
#include "../src/globals.hpp"

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
    //create motor output variables
    int lf_out = 0;
    int lb_out = 0;
    int rf_out = 0;
    int rb_out = 0;

    //take joystick input
    int leftJoyX = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
    int leftJoyY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightJoyX = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
    int rightJoyY = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

    //modify outputs with dead zones
    if (abs(leftJoyX) > deadZone){
        lf_out += leftJoyY;
        lb_out -= leftJoyY;
        rf_out -= leftJoyY;
        rb_out += leftJoyY;
    }
    if (abs(leftJoyY) > deadZone){
        lf_out += leftJoyY;
        lb_out += leftJoyY;
        rf_out += leftJoyY;
        rb_out += leftJoyY;
    }
    if (abs(rightJoyX) > deadZone){
        lf_out -= leftJoyY;
        lb_out -= leftJoyY;
        rf_out += leftJoyY;
        rb_out += leftJoyY;
    }
}
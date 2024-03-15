//includes
#include "main.h"
#include "../src/globals.hpp"

//local globals
double angleRadians = 1.57079632679;
double deltaL = l_rot.get_position() - lTrackPrev;;
double lTrackPrev = l_rot.get_position();
double rTrackPrev = r_rot.get_position();

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
    //turning track for field relative strafing
    double deltaL = l_rot.get_position() - lTrackPrev;
    double deltaR = r_rot.get_position() - rTrackPrev;
    double deltaTheta = (deltaL - deltaR)/16;
    angleRadians += deltaTheta;

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

    //modify outputs with dead zones and global strafe
    if (abs(leftJoyX) > deadZone){
        lf_out += leftJoyY*cos(angleRadians) + rightJoyX*sin(angleRadians); //lf_out += leftJoyX;
        lb_out -= leftJoyY*cos(angleRadians) + rightJoyX*sin(angleRadians); //lb_out -= leftJoyX;
        rf_out -= leftJoyY*cos(angleRadians) + rightJoyX*sin(angleRadians); //rf_out -= leftJoyX;
        rb_out += leftJoyY*cos(angleRadians) + rightJoyX*sin(angleRadians); //rb_out += leftJoyX;
    }
    if (abs(leftJoyY) > deadZone){
        lf_out += leftJoyY*sin(angleRadians) - rightJoyX*cos(angleRadians); //lf_out += leftJoyY;
        lb_out += leftJoyY*sin(angleRadians) - rightJoyX*cos(angleRadians); //lb_out += leftJoyY;
        rf_out += leftJoyY*sin(angleRadians) - rightJoyX*cos(angleRadians); //rf_out += leftJoyY;
        rb_out += leftJoyY*sin(angleRadians) - rightJoyX*cos(angleRadians); //rb_out += leftJoyY;
    }
    if (abs(rightJoyX) > deadZone){
        lf_out -= rightJoyX;
        lb_out -= rightJoyX;
        rf_out += rightJoyX;
        rb_out += rightJoyX;
    }

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

    //update motor velocity
    lf_mtr.move_velocity(200*lf_out);
    lb_mtr.move_velocity(200*lb_out);
    rf_mtr.move_velocity(200*rf_out);
    rb_mtr.move_velocity(200*rb_out);
}
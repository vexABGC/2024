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
    //turning track for field relative strafing
    //double deltaL = l_rot.get_position() - lTrackPrev;
    //double deltaR = r_rot.get_position() - rTrackPrev;
    //double deltaTheta = (deltaL - deltaR)/16;
    //angleRadians += deltaTheta;
    master.print(1, 1, "hi");

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

        std::cout << leftJoyX << " ";
        std::cout << leftJoyY << " ";
        std::cout << rightJoyX << " ";
        std::cout << rightJoyY << std::endl;

        //create drive, strafe, and turn desired values based on rotation
        double strafe = leftJoyX;
        double drive = leftJoyY;
        double turn = rightJoyX;

        //scale down drive and strafe by sqrt(2) to help with maxing out early
        strafe /= sqrt(2);
        drive /= sqrt(2);

        //create outputs with global strafe
        int lf_out = maxDriveRPM * (drive + strafe + turn);
        int lb_out = maxDriveRPM * (drive - strafe + turn);
        int rf_out = maxDriveRPM * (drive - strafe - turn);
        int rb_out = maxDriveRPM * (drive + strafe - turn);

        //fix scaling if output > 1
        //int max = lf_out;
        //if (max < lb_out) max = lb_out;
        //if (max < rf_out) max = rf_out;
        //if (max < rb_out) max = rb_out;
        //if (max > maxDriveRPM){
        //    lf_out *= maxDriveRPM / max;
        //    lb_out *= maxDriveRPM / max;
        //    rf_out *= maxDriveRPM / max;
        //    rb_out *= maxDriveRPM / max;
        //}

        //update motor velocity
        lf_mtr.move_velocity(200*lf_out);
        lb_mtr.move_velocity(200*lb_out);
        rf_mtr.move_velocity(200*rf_out);
        rb_mtr.move_velocity(200*rb_out);
    }
}
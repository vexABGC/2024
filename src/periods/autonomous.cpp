//includes
#include "main.h"
#include "../src/globals.hpp"
using std::min, std::max;
using namespace okapi;

//auton constants
#define PI 3.141592653589793
#define WHEEL_DIAMETER 4.125
#define WHEEL_TREAD 15.25
#define TURN_ERROR 300

//auton methods
void turnAngle(double degrees, double maxWheelRPM){
    double targetAngle = gyro.get_rotation() + degrees;
    double delta = degrees;

    while ((abs(delta) > 2) || (abs(left_mtrs.get_actual_velocities().at(0)) < 8) || (abs(right_mtrs.get_actual_velocities().at(0)) < 8)){
        double wheelSpeed = min(maxWheelRPM * abs(delta) / 25, maxWheelRPM);
        if (delta > 0){
            left_mtrs.move_velocity(wheelSpeed);
            right_mtrs.move_velocity(-wheelSpeed);
        }else{
            left_mtrs.move_velocity(-wheelSpeed);
            right_mtrs.move_velocity(wheelSpeed);
        }
        delta = targetAngle - gyro.get_rotation();
        std::cout << delta << std::endl;
        pros::delay(20);
    }

    left_mtrs.move(0);
    right_mtrs.move(0);
}

void driveDistance(double inches, double maxWheelRPM){
    double deltaLeft = 36000 * inches / (WHEEL_DIAMETER * PI);
    double deltaRight = deltaLeft;
    double targetLeft = l_rot.get_position() + deltaLeft;
    double targetRight = r_rot.get_position() + deltaRight;

    while (abs(deltaLeft) > TURN_ERROR || abs(deltaRight) > TURN_ERROR || fabs(left_mtrs.get_actual_velocities().at(0)) > 1 || fabs(right_mtrs.get_actual_velocities().at(0)) > 1){
        if (deltaLeft > TURN_ERROR){
            left_mtrs.move_velocity(min(maxWheelRPM * pow(deltaLeft / 10000,5), maxWheelRPM));
        }
        if (-deltaLeft > TURN_ERROR){
            left_mtrs.move_velocity(max(maxWheelRPM * pow(deltaLeft / 10000,5), -maxWheelRPM));
        }
        if (deltaRight > TURN_ERROR){
            right_mtrs.move_velocity(min(maxWheelRPM * pow(deltaRight / 10000,5), maxWheelRPM));
        }
        if (-deltaRight > TURN_ERROR){
            right_mtrs.move_velocity(max(maxWheelRPM * pow(deltaRight / 10000,5), -maxWheelRPM));
        }
        deltaLeft = targetLeft - l_rot.get_position();
        deltaRight = targetRight - r_rot.get_position();
    }
    
    left_mtrs.move(0);
    right_mtrs.move(0);
}

//replay function
//TBD

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
    //auton test code
    left_mtrs.move_velocity(0);
    right_mtrs.move_velocity(0);
    
    //Angle test
    turnAngle(90, 50);

    //Drive test
    driveDistance(12, 50);
}
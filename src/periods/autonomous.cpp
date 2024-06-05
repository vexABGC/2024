//includes
#include "main.h"
#include "../src/globals.hpp"
using std::min, std::max;

//auton constants
#define PI 3.141592653589793
#define WHEEL_DIAMETER 4
#define WHEEL_TREAD 16.5
#define TURN_ERROR 1

//auton globals
double pos_x;
double pox_y;
double angle;

//auton methods
void turnAngle(double degrees, double maxWheelRPM){
    double targetAngle = gyro.get_rotation() + degrees;
    double delta = degrees;

    while (abs(delta) > TURN_ERROR){
        double wheelSpeed = min(maxWheelRPM * abs(delta) / 100, maxWheelRPM);
        if (delta > 0){
            left_mtrs.move_velocity(wheelSpeed);
            right_mtrs.move_velocity(-wheelSpeed);
        }else{
            left_mtrs.move_velocity(-wheelSpeed);
            right_mtrs.move_velocity(wheelSpeed);
        }
        delta = targetAngle - gyro.get_rotation();
    }
}

void driveDistance(double inches, double maxWheelRPM){
    double deltaLeft = 36000 * inches / (WHEEL_DIAMETER * PI);
    double deltaRight = deltaLeft;
    double targetLeft = l_rot.get_position() + deltaLeft;
    double targetRight = r_rot.get_position() + deltaRight;

    while (abs(deltaLeft) > TURN_ERROR || abs(deltaRight) > TURN_ERROR){
        if (deltaLeft > TURN_ERROR){
            left_mtrs.move_velocity(min(maxWheelRPM * deltaLeft / 10000, maxWheelRPM));
        }
        if (-deltaLeft > TURN_ERROR){
            left_mtrs.move_velocity(max(maxWheelRPM * deltaLeft / 10000, -maxWheelRPM));
        }
        if (deltaRight > TURN_ERROR){
            right_mtrs.move_velocity(min(maxWheelRPM * deltaRight / 10000, maxWheelRPM));
        }
        if (-deltaRight > TURN_ERROR){
            right_mtrs.move_velocity(max(maxWheelRPM * deltaRight / 10000, -maxWheelRPM));
        }
        deltaLeft = targetLeft - l_rot.get_position();
        deltaRight = targetRight - r_rot.get_position();
    }
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
    //auton test code
    
    //Angle test
    //turnAngle(90, 200);

    //Drive test
    driveDistance(24, 200);
}
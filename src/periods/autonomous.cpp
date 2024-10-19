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
    //Setup
    gyro.tare_heading();
    l_rot.set_position(0);
    r_rot.set_position(0);
    int targetAngle = 0;
    double target = 2 * 36000 * inches / (WHEEL_DIAMETER * PI);
    double delta = target - l_rot.get_position() - r_rot.get_position();
    int error = 0;
    int heading = 0;

    //Drive loop
    while (abs(delta) > 2 * TURN_ERROR && pros::competition::is_autonomous()){
        //Update motors
        if (delta > 0){
            left_mtrs.move_velocity(min(maxWheelRPM * delta / 72000 + error * 10, maxWheelRPM + error * 10));
            right_mtrs.move_velocity(min(maxWheelRPM * delta / 72000 - error * 10, maxWheelRPM - error * 10));
        }
        //else if (delta < 0){
        //    left_mtrs.move_velocity(max(maxWheelRPM * delta / 72000 - error * 10, -maxWheelRPM - error * 10));
        //    right_mtrs.move_velocity(max(maxWheelRPM * delta / 72000 + error * 10, -maxWheelRPM + error * 10));
        //}

        //Delay
        pros::delay(50);
        heading = (l_rot.get_position() - r_rot.get_position())/(WHEEL_TREAD * 100);

        //Calculate delta and error
        delta = target - l_rot.get_position() - r_rot.get_position();
        error = targetAngle - heading;
    }

    //Stop
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
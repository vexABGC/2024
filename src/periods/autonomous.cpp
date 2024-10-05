//includes
#include "main.h"
#include "../src/globals.hpp"
//using std::min, std::max;
using namespace okapi;

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
/*
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

    while (abs(deltaLeft) > TURN_ERROR || abs(deltaRight) > TURN_ERROR || fabs(left_mtrs.get_voltages().at(0)) > 5 || fabs(right_mtrs.get_voltages().at(0)) > 5){
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
*/

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
    
    //Angle test
    //turnAngle(90, 150);

    //Drive test
    //driveDistance(24, 200);

    //okapi setup
    std::shared_ptr<OdomChassisController> chassis = ChassisControllerBuilder()
        //Blue inserts, 4.125" omni wheels, 15" wheel track
        .withMotors({LF_PRT, LB_PRT}, {RF_PRT, RB_PRT})
        .withDimensions(AbstractMotor::gearset::blue, {{4.125_in, 15_in}, imev5BlueTPR})
        .withSensors(
            RotationSensor({L_ROT_PRT, false}),
            RotationSensor({R_ROT_PRT, true})
        )
        .withOdometry({{4.125_in, 15_in}, quadEncoderTPR}, StateMode::FRAME_TRANSFORMATION)
        .buildOdometry();
    
    
    chassis->setState({0_in, 0_in, 0_deg});
    chassis->setMaxVelocity(50);
    chassis->driveToPoint({1_ft, 1_ft});
    pros::delay(2000);
    chassis->driveToPoint({1_ft, 2_ft});
    pros::delay(2000);
    chassis->driveToPoint({0_ft, 0_ft});
    pros::delay(2000);
    chassis->turnToAngle(0_deg);
}
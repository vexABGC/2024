//includes
#include "main.h"
#include "../src/globals.hpp"
using namespace okapi;

//auton constants
#define PI 3.141592653589793
#define WHEEL_DIAMETER 4.125
#define WHEEL_TREAD 15.25
#define TURN_ERROR 300

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
    //okapi setup
    left_mtrs.move_velocity(0);
    right_mtrs.move_velocity(0);
    std::shared_ptr<OdomChassisController> chassis = ChassisControllerBuilder()
        //Blue inserts, 4.125" omni wheels, 15" wheel track
        .withMotors({LF_PRT, LB_PRT}, {RF_PRT, RB_PRT})
        .withGains(
            {0.004, 0, 0.0003}, //Distance gain
            {0.001, 0, 0.0001}, //Turn gains
            {0.0003, 0, 0.0003}  //Angle gains
        )
        .withDimensions(AbstractMotor::gearset::blue, {{4_in, 15.125_in}, imev5BlueTPR})
        .withSensors(
            RotationSensor{L_ROT_PRT, false},
            RotationSensor{R_ROT_PRT, false}
        )
        .withOdometry({{4.125_in, 15_in}, quadEncoderTPR}, StateMode::CARTESIAN)
        .buildOdometry();
    
    
    chassis->setState({0_in, 0_in, 0_deg});
    chassis->setMaxVelocity(100);
    chassis->turnToAngle(90_deg);
    chassis->moveDistance(1_ft);
}
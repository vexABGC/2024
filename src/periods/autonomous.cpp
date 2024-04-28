//includes
#include "main.h"
#include "../src/globals.hpp"
using namespace okapi;

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
    //create chassis
    std::shared_ptr<okapi::OdomChassisController> chassis = ChassisControllerBuilder()
        .withMotors(lf_prt, rf_prt, rb_prt, lf_prt)
        .withDimensions(AbstractMotor::gearset::green, {{2.75_in, 13_in, 2_in, 2.75_in}, imev5GreenTPR})
        .withGains(
            {0.001, 0.001, 0.001}, // Lateral error
            {0.001, 0.001, 0.001}, // Turning error
            {0.001, 0.001, 0.001} // Straight drive assist error
        )
        //.withSensors(
        //    okapi::ADIEncoder{'B', 'C'}, // left encoder
        //    okapi::ADIEncoder{'D', 'E', true}, // right encoder
        //    okapi::ADIEncoder{'F', 'G'}  // middle encoder
        //)
        .withOdometry()
        .buildOdometry();
    
    //drive test
    chassis->driveToPoint({1_ft, 1_ft});
}
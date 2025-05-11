//Includes
#include "main.h"
#include "../src/globals.hpp"
#include "../src/autons/autons.hpp"
#include "../src/graphics/autonPage.hpp"
#include "../src/control/controllerScreen.hpp"
#include "pros/motors.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    //Calibrate
    pros::delay(500);
    constants();
    chassis.odom_tracker_right_set(&v_tracker);
    chassis.odom_tracker_back_set(&h_tracker);
    chassis.drive_brake_set(pros::E_MOTOR_BRAKE_BRAKE);

    //Lady brown setup
    lady_brown_mtr.tare_position();
    ladyBrownAngle = 0;
    chassis.initialize();

    //GUI
    AutonPage::initialize(); //Alphabetical order
    AutonPage("B R M", "Blue Risky Mogo", blueRiskyMogo);
    AutonPage("B R R", "Blue Risky Ring", blueRiskyRing);
    AutonPage("B S M", "Blue Safe Mogo", blueSafeMogo);
    AutonPage("B S R", "Blue Safe Ring", blueSafeRing);
    AutonPage("R R M", "Red Risky Mogo", redRiskyMogo);
    AutonPage("R R R", "Red Risky Ring", redRiskyRing);
    AutonPage("R S M", "Red Safe Mogo", redSafeMogo);
    AutonPage("R S R", "Red Safe Ring", redSafeRing);
    AutonPage("SL", "Straight line", line);
}
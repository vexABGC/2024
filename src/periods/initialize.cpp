//Includes
#include "EZ-Template/sdcard.hpp"
#include "main.h"
#include "../src/globals.hpp"
#include "../src/autons/autons.hpp"
#include "../src/control/controllerScreen.hpp"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    //Calibrate
    chassis.odom_tracker_left_set(&v_tracker);
    chassis.odom_tracker_front_set(&h_tracker);
    constants();
    ez::as::auton_selector.autons_add({
        {"Measure offsets", measureOffsets},
        {"Risky Mogo Red", riskyMogo},
        {"Risky Mogo Blue", riskyMogo},
        {"Safe Mogo Red", riskyMogo},
        {"Safe Mogo Blue", riskyMogo},
        {"Risky Ring Red", riskyMogo},
        {"Risky Ring Blue", riskyMogo},
        {"Safe Ring Red", riskyMogo},
        {"Safe Ring Blue", riskyMogo},
    });
    chassis.initialize();
    ez::as::initialize();

    //Lady brown setup
    lady_brown_mtr.tare_position();
    ladyBrownAngle = 0;
}
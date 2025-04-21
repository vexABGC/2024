//Includes
#include "liblvgl/extra/widgets/tabview/lv_tabview.h"
#include "main.h"
#include "../src/globals.hpp"
#include "../src/autons/autons.hpp"
#include "../src/graphics/autonPage.hpp"
#include "../src/control/controllerScreen.hpp"
#include "pros/rtos.hpp"
#include <cstdio>

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
    //ez::as::auton_selector.autons_add({
    //    {"Measure offsets", measureOffsets},
    //    {"Risky Mogo Red", riskyMogo},
    //    {"Risky Mogo Blue", riskyMogo},
    //    {"Safe Mogo Red", riskyMogo},
    //    {"Safe Mogo Blue", riskyMogo},
    //    {"Risky Ring Red", riskyMogo},
    //    {"Risky Ring Blue", riskyMogo},
    //    {"Safe Ring Red", riskyMogo},
    //    {"Safe Ring Blue", riskyMogo},
    //});
    //chassis.initialize();

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
    AutonPage("M O", "Measure Offsets", measureOffsets);

    while (true){
        //Print act tab number and run its callback function every 1000ms
        int tab = lv_tabview_get_tab_act(AutonPage::tabView);
        printf("Tab %d\n", tab);
        AutonPage::callbacks[tab]();
        pros::delay(1000);
    }

    //Lady brown setup
    lady_brown_mtr.tare_position();
    ladyBrownAngle = 0;
}
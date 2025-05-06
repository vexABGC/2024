//Includes
#include "main.h"
#include "../src/globals.hpp"
#include "../src/autons/autons.hpp"
#include "../src/graphics/autonPage.hpp"
#include "../control/toInch.hpp"
#include "pros/misc.hpp"

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
    //Constants
    constants();

    //Call active tab callback function
    AutonPage::callbacks[lv_tabview_get_tab_act(AutonPage::tabView)]();
    
    //Wait
    while (pros::competition::is_autonomous()){
        pros::delay(500);
    }
}
//Includes
#include "main.h"
#include "../src/globals.hpp"
#include "../src/control/movement.hpp"
#include "../src/control/controllerScreen.hpp"
#include "pros/misc.hpp"
#include <fstream>

//Big globals
char inputsRecord[4200] = {};

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
    //Local globals
    int recordCount{0};
    bool autoSpotterTriggered = false;

    //Motor tare
    left_mtrs.tare_position_all();
    right_mtrs.tare_position_all();
    lastL = 0;
    lastR = 0;

    //Main loop
    while (true){

        //Take inputs
        char triggersMaster =
            master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) << 7 |
            master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1) << 6 |
            master.get_digital(pros::E_CONTROLLER_DIGITAL_L2) << 5 |
            master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2) << 4 |
            master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) << 3 |
            master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1) << 2 |
            master.get_digital(pros::E_CONTROLLER_DIGITAL_R2) << 1 |
            master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2) << 0;
        char dpadMaster =
            master.get_digital(pros::E_CONTROLLER_DIGITAL_UP) << 7 |
            master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP) << 6 |
            master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN) << 5 |
            master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN) << 4 |
            master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) << 3 |
            master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT) << 2 |
            master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT) << 1 |
            master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT) << 0;
        char abxyMaster =
            master.get_digital(pros::E_CONTROLLER_DIGITAL_A) << 7 |
            master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A) << 6 |
            master.get_digital(pros::E_CONTROLLER_DIGITAL_B) << 5 |
            master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B) << 4 |
            master.get_digital(pros::E_CONTROLLER_DIGITAL_X) << 3 |
            master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X) << 2 |
            master.get_digital(pros::E_CONTROLLER_DIGITAL_Y) << 1 |
            master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y) << 0;
            
        int inputs[14];
        inputs[0] = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
        inputs[1] = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        inputs[2] = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        inputs[3] = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
        inputs[4] = triggersMaster;
        inputs[5] = dpadMaster;
        inputs[6] = abxyMaster;

        if (partner.is_connected()){
            char triggersPartner =
                partner.get_digital(pros::E_CONTROLLER_DIGITAL_L1) << 7 |
                partner.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1) << 6 |
                partner.get_digital(pros::E_CONTROLLER_DIGITAL_L2) << 5 |
                partner.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2) << 4 |
                partner.get_digital(pros::E_CONTROLLER_DIGITAL_R1) << 3 |
                partner.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1) << 2 |
                partner.get_digital(pros::E_CONTROLLER_DIGITAL_R2) << 1 |
                partner.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2) << 0;
            char dpadPartner =
                partner.get_digital(pros::E_CONTROLLER_DIGITAL_UP) << 7 |
                partner.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP) << 6 |
                partner.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN) << 5 |
                partner.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN) << 4 |
                partner.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) << 3 |
                partner.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT) << 2 |
                partner.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT) << 1 |
                partner.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT) << 0;
            char abxyPartner =
                partner.get_digital(pros::E_CONTROLLER_DIGITAL_A) << 7 |
                partner.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A) << 6 |
                partner.get_digital(pros::E_CONTROLLER_DIGITAL_B) << 5 |
                partner.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B) << 4 |
                partner.get_digital(pros::E_CONTROLLER_DIGITAL_X) << 3 |
                partner.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X) << 2 |
                partner.get_digital(pros::E_CONTROLLER_DIGITAL_Y) << 1 |
                partner.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y) << 0;

            inputs[7] = partner.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
            inputs[8] = partner.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
            inputs[9] = partner.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
            inputs[10] = partner.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
            inputs[11] = triggersPartner;
            inputs[12] = dpadPartner;
            inputs[13] = abxyPartner;
        }else{
            inputs[7] = 0;
            inputs[8] = 0;
            inputs[9] = 0;
            inputs[10] = 0;
            inputs[11] = 0;
            inputs[12] = 0;
            inputs[13] = 0;
        }


        //Movement
        movement(inputs);

        updateControllerScreen(); // Update the controller screen

        pros::delay(50);
    }
}
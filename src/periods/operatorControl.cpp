//Includes
#include "main.h"
#include "../../include/lemlib/timer.hpp"
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
    bool autospotterTriggered = false;

    //Timer for autospotter set for 1:45
    lemlib::Timer autospotterTimer = lemlib::Timer(105000);

    //Force reenable intake
    intakeDirection = 1;

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

        //Recording
        if(shouldRecord){
            //Rumble if start of record
            if (recordCount == 0){
                master.rumble(". .");
            }

            //Record
            for (int i = 0; i < 14; i++){
                inputsRecord[recordCount*14 + i] = inputs[i];
            }

            //Save if end of record
            if (recordCount == 299){
                //Open file
                std::ofstream file("/usd/sigma.auton", std::ios::binary);

                for (int i = 0; i < 299*14; i++){
                    file.write(reinterpret_cast<const char*>(&(inputsRecord[i])), 1);
                }
                file.close();

                //End record
                shouldRecord = false;
                recordCount = 0;
                master.rumble("..");
                record_button_style.body.main_color = LV_COLOR_BLACK;
                record_button_style.body.grad_color = LV_COLOR_BLACK;
                lv_btn_set_style(record_button, LV_BTN_STYLE_REL, &record_button_style);
            }
            recordCount++;
        }
        // Autospotter
        if (pros::competition::is_connected() && !autospotterTriggered && autospotterTimer.getTimeSet() < 20000) {
            autospotterTriggered = true;
            raiseControllerWarning("Autospotter","Last 20 seconds!",". . .",5);
        }

        updateControllerScreen(); // Update the controller screen

        pros::delay(50);
    }
}
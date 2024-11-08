//includes
#include "main.h"
#include "../src/globals.hpp"
#include "../src/control/movement.hpp"
#include <sstream>
#include <fstream>
#include <iomanip>

//big globals
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
    int loopCount{0};
    int recordCount{0};
    lastLF = lf_mtr.get_position();
    lastLM = lm_mtr.get_position();
    lastLB = lb_mtr.get_position();
    lastRF = rf_mtr.get_position();
    lastRM = rm_mtr.get_position();
    lastRB = rb_mtr.get_position();
    arm_piston.set_value(1);

    //Main loop
    while (true){
        //Controller screen overheat display (staggered to not violate 50ms in bewteen updates)
        if (loopCount % 80 == 0){
            master.clear();
        }
        else if (loopCount % 80 == 1){
            partner.clear();
        }
        else if (loopCount % 8 == 2){
            std::stringstream line("");
            line << "LF-" << lf_mtr.is_over_temp() << " ";
            line << "LB-" << lb_mtr.is_over_temp() << " ";
            line << "RF-" << rf_mtr.is_over_temp() << " ";
            line << "RB-" << rb_mtr.is_over_temp() << " ";
            master.set_text(0, 0, line.str());
        }else if (loopCount % 8 == 3){
            std::stringstream line("");
            line << "LF-" << lf_mtr.is_over_temp() << " ";
            line << "LB-" << lb_mtr.is_over_temp() << " ";
            line << "RF-" << rf_mtr.is_over_temp() << " ";
            line << "RB-" << rb_mtr.is_over_temp() << " ";
            partner.set_text(0, 0, line.str());
        }else if (loopCount % 8 == 4){
            std::stringstream line("");
            line << "ARM-" << 0 << " ";
            line << "INT-" << intake_mtrs.are_over_temp().at(0) + intake_mtrs.are_over_temp().at(1) << " ";
            master.set_text(1, 0, line.str());
        }else if (loopCount % 8 == 5){
            std::stringstream line("");
            line << "ARM-" << 0 << " ";
            line << "INT-" << intake_mtrs.are_over_temp().at(0) + intake_mtrs.are_over_temp().at(1) << " ";
            partner.set_text(1, 0, line.str());
        }else if (loopCount % 8 == 6){
            std::stringstream line("");
            line << "MOGO COUNT-" << mogoVal;
            master.set_text(2, 0, line.str());
        }else if (loopCount % 8 == 7){
            std::stringstream line("");
            line << "MOGO COUNT-" << mogoVal;
            partner.set_text(2, 0, line.str());
        }

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
                lv_obj_clean(dSelect);
                lv_label_set_text(lv_label_create(dSelect, NULL), "recording finsihed");
            }
            recordCount++;
        }
        pros::delay(50);
        loopCount++;
    }
}
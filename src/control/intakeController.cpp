//Includes
#include "main.h"
#include "../src/control/intakeController.hpp"
#include "../src/globals.hpp"

//Method definition
void intakeController(){
    //Set color sensor mode
    color_sensor.disable_gesture();
    //Main loop
    while (true){
        //Check if auton or op control
        if (pros::competition::is_disabled()){
            //Disabled, don't run intake
            intake_top_mtr.move(0);
            pros::delay(50);
            continue;
        }

        //Check if sorting enabled
        if (sortingEnabled.load()){
            //Sorting enabled
            //Check if color detected is close enough
            if(color_sensor.get_proximity() < 50){
                //Not close enough, just keep running
                intake_top_mtr.move(INTAKE_TOP_MULTIPLIER * 127);
                continue;
            }

            //Check color, and respond
            if (color_sensor.get_hue() < 30 || color_sensor.get_hue() > 330){
                //Red ring detected, check selected color and respond
                if (color.load() == 0){
                    //Red ring is enabled, keep moving
                    intake_top_mtr.move(INTAKE_TOP_MULTIPLIER * 127);
                }else{
                    //Blue ring is enabled, expel
                    intake_top_mtr.move(INTAKE_TOP_MULTIPLIER * -127);
                    pros::delay(300);
                }
            }else if(color_sensor.get_hue() > 150 && color_sensor.get_hue() < 270){
                //Blue ring, check selected color and respond
                if (color.load() == 1){
                    //Blue ring is enabled, keep moving
                    intake_top_mtr.move(INTAKE_TOP_MULTIPLIER * 127);
                }else{
                    //Red ring is enabled, expel
                    intake_top_mtr.move(INTAKE_TOP_MULTIPLIER * -127);
                    pros::delay(300);
                }
            }else{
                //Error color, just keep running
                intake_top_mtr.move(INTAKE_TOP_MULTIPLIER * 127);
            }
        }else{
            //Sorting not enabled, just run
            intake_top_mtr.move(INTAKE_TOP_MULTIPLIER * 127);
        }

        //Standard delay
        pros::delay(50);
    }
}
//Includes
#include "main.h"
#include "../src/control/intakeController.hpp"
#include "../src/globals.hpp"

//Method definition
void intakeController(){
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
            //Sorting enabled, not implemented, just run
            intake_top_mtr.move(0.8 * 127);
        }else{
            //Sorting not enabled, just run
            intake_top_mtr.move(0.8 * 127);
        }
    }
}
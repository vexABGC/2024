//includes
#include "main.h"
#include "../src/control/intakeController.hpp"
#include "../src/globals.hpp"

//method definition
void intakeController(){
    //main loop
    while (true){
        //variables
        int direction = intakeTopAmount.load();
        int detectedColor = 3;

        //check if sorting enabled
        if (sortingEnabled.load()){
            //sorting enabled
            //check if ring is near
            if (color_sensor.get_proximity() > 150){
                //check ring color 
                if (color_sensor.get_hue() < 30 || color_sensor.get_hue() > 330){
                    //red ring
                    detectedColor = 0;
                }else if(color_sensor.get_hue() > 150 && color_sensor.get_hue() < 270){
                    //blue ring
                    detectedColor = 1;
                }else if(color_sensor.get_hue() > 30 && color_sensor.get_hue() < 60){
                    //teammate's hand
                    detectedColor = 2;
                }
            }

            //update direction if wrong color
            if (detectedColor == 3){
                //error color, allow input as normal
                intake_top_mtr.move(direction);
            }else if(detectedColor == 2){
                //shred teammate's hand
                intake_top_mtr.move(0.8 * 127);
            }else if (detectedColor == color){
                //correct ring, allow input as normal
                intake_top_mtr.move(direction);
            }else if((detectedColor + 1) % 2 == color){
                //wrong ring, expel backwards
                intake_top_mtr.move(-127);
                pros::delay(300);
            }
        }else {
            //sorting disabled
            intake_top_mtr.move(direction);
        }

        //delay
        pros::delay(50);
    }
}
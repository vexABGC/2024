//includes
#include "main.h"
#include "../src/control/ledStrobe.hpp"

//method definition
void ledStrobe(){
    //led strobe
    for (uint8_t ledNum = 8; ledNum > 0; ledNum--){
        pros::ADIDigitalOut ledOn(ledNum, 0);
        pros::delay(62.5);
    }
    pros::delay(1000);
    for (uint8_t ledNum = 8; ledNum > 0; ledNum--){
        pros::ADIDigitalOut ledOn(ledNum, 1);
        pros::delay(62.5);
    }
}
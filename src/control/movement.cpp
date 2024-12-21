//Includes
#include "main.h"
#include "../src/control/movement.hpp"
#include "../src/globals.hpp"

//Method definition
void movement(int inputs[14]){
    //Make simple master values
    int masterLeftX = inputs[0];
    int masterLeftY = inputs[1];
    int masterRightX = inputs[2];
    int masterRightY = inputs[3];
    int masterCurL1 = (inputs[4] >> 7) & 1;
    int masterNewL1 = (inputs[4] >> 6) & 1;
    int masterCurL2 = (inputs[4] >> 5) & 1;
    int masterNewL2 = (inputs[4] >> 4) & 1;
    int masterCurR1 = (inputs[4] >> 3) & 1;
    int masterNewR1 = (inputs[4] >> 2) & 1;
    int masterCurR2 = (inputs[4] >> 1) & 1;
    int masterNewR2 = (inputs[4] >> 0) & 1;
    int masterCurUp = (inputs[5] >> 7) & 1;
    int masterNewUp = (inputs[5] >> 6) & 1;
    int masterCurDown = (inputs[5] >> 5) & 1;
    int masterNewDown = (inputs[5] >> 4) & 1;
    int masterCurLeft = (inputs[5] >> 3) & 1;
    int masterNewLeft = (inputs[5] >> 2) & 1;
    int masterCurRight = (inputs[5] >> 1) & 1;
    int masterNewRight = (inputs[5] >> 0) & 1;
    int masterCurA = (inputs[6] >> 7) & 1;
    int masterNewA = (inputs[6] >> 6) & 1;
    int masterCurB = (inputs[6] >> 5) & 1;
    int masterNewB = (inputs[6] >> 4) & 1;
    int masterCurX = (inputs[6] >> 3) & 1;
    int masterNewX = (inputs[6] >> 2) & 1;
    int masterCurY = (inputs[6] >> 1) & 1;
    int masterNewY = (inputs[6] >> 0) & 1;

    //Make simple partner values
    int partnerLeftX = inputs[7];
    int partnerLeftY = inputs[8];
    int partnerRightX = inputs[9];
    int partnerRightY = inputs[10];
    int partnerCurL1 = (inputs[11] >> 7) & 1;
    int partnerNewL1 = (inputs[11] >> 6) & 1;
    int partnerCurL2 = (inputs[11] >> 5) & 1;
    int partnerNewL2 = (inputs[11] >> 4) & 1;
    int partnerCurR1 = (inputs[11] >> 3) & 1;
    int partnerNewR1 = (inputs[11] >> 2) & 1;
    int partnerCurR2 = (inputs[11] >> 1) & 1;
    int partnerNewR2 = (inputs[11] >> 0) & 1;
    int partnerCurUp = (inputs[12] >> 7) & 1;
    int partnerNewUp = (inputs[12] >> 6) & 1;
    int partnerCurDown = (inputs[12] >> 5) & 1;
    int partnerNewDown = (inputs[12] >> 4) & 1;
    int partnerCurLeft = (inputs[12] >> 3) & 1;
    int partnerNewLeft = (inputs[12] >> 2) & 1;
    int partnerCurRight = (inputs[12] >> 1) & 1;
    int partnerNewRight = (inputs[12] >> 0) & 1;
    int partnerCurA = (inputs[13] >> 7) & 1;
    int partnerNewA = (inputs[13] >> 6) & 1;
    int partnerCurB = (inputs[13] >> 5) & 1;
    int partnerNewB = (inputs[13] >> 4) & 1;
    int partnerCurX = (inputs[13] >> 3) & 1;
    int partnerNewX = (inputs[13] >> 2) & 1;
    int partnerCurY = (inputs[13] >> 1) & 1;
    int partnerNewY = (inputs[13] >> 0) & 1;
    
    //Apply dead zone to joysticks
    masterLeftX = (abs(masterLeftX) < DEAD_ZONE) ? 0 : masterLeftX;
    masterLeftY = (abs(masterLeftY) < DEAD_ZONE) ? 0 : masterLeftY;
    masterRightX = (abs(masterRightX) < DEAD_ZONE) ? 0 : masterRightX;
    masterRightY = (abs(masterRightY) < DEAD_ZONE) ? 0 : masterRightY;
    partnerLeftX = (abs(partnerLeftX) < DEAD_ZONE) ? 0 : partnerLeftX;
    partnerLeftY = (abs(partnerLeftY) < DEAD_ZONE) ? 0 : partnerLeftY;
    partnerRightX = (abs(partnerRightX) < DEAD_ZONE) ? 0 : partnerRightX;
    partnerRightY = (abs(partnerRightY) < DEAD_ZONE) ? 0 : partnerRightY;

    //Movement
    if (masterLeftY != 0 || masterRightX != 0){
        left_mtrs.move(SPEED_MULTIPLIER * (masterLeftY + masterRightX));
        right_mtrs.move(SPEED_MULTIPLIER * (masterLeftY - masterRightX));
        lastLF = lf_mtr.get_position();
        lastLM = lm_mtr.get_position();
        lastLB = lb_mtr.get_position();
        lastRF = rf_mtr.get_position();
        lastRM = rm_mtr.get_position();
        lastRB = rb_mtr.get_position();

    }else{
        lf_mtr.move_absolute(lastLF, 200 * BRAKE_MULTIPLIER);
        lm_mtr.move_absolute(lastLM, 200 * BRAKE_MULTIPLIER);
        lb_mtr.move_absolute(lastLB, 200 * BRAKE_MULTIPLIER);
        rf_mtr.move_absolute(lastRF, 200 * BRAKE_MULTIPLIER);
        rm_mtr.move_absolute(lastRM, 200 * BRAKE_MULTIPLIER);
        rb_mtr.move_absolute(lastRB, 200 * BRAKE_MULTIPLIER);
    }

    //Pneumatics
    if (masterNewY || partnerNewY){
        mogoVal++;
        mogo_piston.set_value(mogoVal % 2);
    }

    //Sorting
    if (masterNewB || partnerNewB){
        sortingEnabled = !sortingEnabled;
    }

    //Intake top
    if (masterCurR1 || masterCurR2){
        //Master control
        intakeTopAmount = 127 * (masterCurR1 - masterCurR2);
    }else if (partnerCurR1 || partnerCurR2){
        //Partner control
        intakeTopAmount = 127 * (partnerCurR1 - partnerCurR2);
    }else if (partnerRightY != 0){
        intakeTopAmount = partnerRightY;
    }else{
        intakeTopAmount = 0;
    }

    //Intake bottom
    if (masterCurL1 || masterCurL2){
        //Master control
        intake_bot_mtr.move(127 * (
            masterCurL1 - masterCurL2
        ));
    }else if (partnerCurL1 || partnerCurL2){
        //Partner control
        intake_bot_mtr.move(127 * (
            partnerCurL1 - partnerCurL2
        ));
    }else if (partnerLeftY != 0){
        intake_bot_mtr.move(partnerLeftY);
    }else{
        intake_bot_mtr.move(0);
    }

    //Corner mech
    if (masterNewRight){
        cornerAngle = (cornerAngle + 170) % 340;
    }else 
    if (partnerNewRight){
        cornerAngle = (cornerAngle + 170) % 340;
    }
    corner_mtr.move_absolute(cornerAngle, 50);
}
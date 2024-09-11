//includes
#include "main.h"
#include "../src/globals.hpp"

//local globals
double armAngle = 0;

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
    //brake setup
    double lastLF{lf_mtr.get_position()};
    double lastLB{lb_mtr.get_position()};
    double lastRF{rf_mtr.get_position()};
    double lastRB{rb_mtr.get_position()};

    //Main loop
    while (true){
        //take joystick input
        int leftJoyY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightJoyX = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        //apply dead zones to joysticks
        leftJoyY = (abs(leftJoyY) < DEAD_ZONE) ? 0 : leftJoyY;
        rightJoyX = (abs(rightJoyX) < DEAD_ZONE) ? 0 : rightJoyX;

        //update motors
        if (leftJoyY != 0 || rightJoyX != 0){
            left_mtrs.move((leftJoyY + rightJoyX) * SPEED_MULTIPLIER);
            right_mtrs.move((leftJoyY - rightJoyX) * SPEED_MULTIPLIER);
            lastLF = lf_mtr.get_position();
            lastLB = lb_mtr.get_position();
            lastRF = rf_mtr.get_position();
            lastRB = rb_mtr.get_position();
        }else{
            lf_mtr.move_absolute(lastLF, 600 * SPEED_MULTIPLIER);
            lb_mtr.move_absolute(lastLB, 600 * SPEED_MULTIPLIER);
            rf_mtr.move_absolute(lastRF, 600 * SPEED_MULTIPLIER);
            rb_mtr.move_absolute(lastRB, 600 * SPEED_MULTIPLIER);
        }

        //pneumatics
        mogo_piston.set_value(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1));

        //intake
        intake_mtr.move(127 * 0.6 * (
            master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)
            - master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)
        ));

        //arm movement
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)
        - master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) != 0){
            arm_mtr.move_velocity(ARM_VELOCITY * (
                master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)
                - master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)
            ));
            armAngle = arm_mtr.get_position();
        }else{
            arm_mtr.move_absolute(armAngle, ARM_VELOCITY);
        }

        //arm pos hold
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) != 0 &&
            master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) != 0){
            if (master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)){ //shared wall stake (high)
                arm_mtr.move_absolute(ARM_HIGH_ANGLE, ARM_VELOCITY);
            }else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B)){ //alliance wall stake (medium)
                arm_mtr.move_absolute(ARM_MED_ANGLE, ARM_VELOCITY);
            }else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)){ //ground (low)
                arm_mtr.move_absolute(ARM_LOW_ANGLE, ARM_VELOCITY);
            }else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){ //recalibrate
                //not implemented
            }
        }

        pros::delay(20);     
    }
}
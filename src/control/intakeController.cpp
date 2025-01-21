//Includes
#include "../src/control/intakeController.hpp"
#include "../src/globals.hpp"

//Method definition
void intakeController(){
    //Set color sensor mode
    color_sensor.disable_gesture();
    color_sensor.set_integration_time(3);
    color_sensor.set_led_pwm(100);

    //Main loop
    while (true){
        //Check if auton or op control
        if (pros::competition::is_disabled()){
            //Disabled, don't run intake
            intake_top_mtr.move(0);
            pros::delay(50);
            continue;
        }

        //Check if off
        if (intakeDirection.load() == 0){
            //Intake off, don't run intake
            intake_top_mtr.move(0);
            std::cout << color_sensor.get_proximity() << " " << color_sensor.get_hue() << std::endl;
            pros::delay(50);
            continue;
        }

        //Check if reversed (only used in auton for dropping intake)
        if (intakeDirection.load() == 0){
            //Intake reversed, run backwards, no sorting
            intake_top_mtr.move(-127 * INTAKE_TOP_MULTIPLIER);
            pros::delay(50);
            continue;
        }

        //Check if sorting enabled
        if (sortingEnabled.load()){
            //Sorting enabled
            //Check if color detected is close enough
            if(color_sensor.get_proximity() < 255){
                //Not close enough, just keep running
                intake_top_mtr.move(INTAKE_TOP_MULTIPLIER * 127);
                continue;
            }

            //Check color, and respond
            if (color_sensor.get_hue() < 50 || color_sensor.get_hue() > 330){
                //Red ring detected, check selected color and respond
                if (color.load() == 0){
                    //Red ring is enabled, keep moving
                    intake_top_mtr.move(INTAKE_TOP_MULTIPLIER * 127);
                }else{
                    //Blue ring is enabled, expel
                    intake_top_mtr.tare_position();
                    int targetPos = intake_top_mtr.get_position() + 220;
                    intake_top_mtr.move_absolute(targetPos, 200);
                    while (intake_top_mtr.get_actual_velocity() > 5 || fabs(intake_top_mtr.get_position() - targetPos) > 10){
                        intake_top_mtr.move_absolute(targetPos, 200);
                        pros::delay(3);
                    }
                    targetPos -= 50;
                    intake_top_mtr.move_absolute(targetPos, 200);
                    pros::delay(500);
                }
            }else if(color_sensor.get_hue() > 180 && color_sensor.get_hue() < 270){
                //Blue ring, check selected color and respond
                if (color.load() == 1){
                    //Blue ring is enabled, keep moving
                    intake_top_mtr.move(INTAKE_TOP_MULTIPLIER * 127);
                }else{
                    //Red ring is enabled, expel
                    intake_top_mtr.tare_position();
                    int targetPos = intake_top_mtr.get_position() + 220;
                    intake_top_mtr.move_absolute(targetPos, 200);
                    while (intake_top_mtr.get_actual_velocity() > 5 || fabs(intake_top_mtr.get_position() - targetPos) > 10){
                        intake_top_mtr.move_absolute(targetPos, 200);
                        pros::delay(3);
                    }
                    targetPos -= 50;
                    intake_top_mtr.move_absolute(targetPos, 200);
                    pros::delay(500);
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
        pros::delay(3);
    }
}
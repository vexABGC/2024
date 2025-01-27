//Includes
#include "../src/control/intakeController.hpp"
#include "../src/globals.hpp"

//Method definition
void intakeController(){
    //Set color sensor mode
    color_sensor.disable_gesture();
    color_sensor.set_integration_time(50);
    color_sensor.set_led_pwm(100);

    //Tare position
    intake_top_mtr.set_zero_position(230);

    //Main loop
    while (true){
        //Check if overridden off
        if (intakeDirection.load() == -2){
            //Intake to have no updates at all, being managed elsewhere
            pros::delay(50);
            continue;
        }

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
            pros::delay(50);
            continue;
        }

        //Check if sorting enabled
        if (sortingEnabled.load()){
            //Sorting enabled
            //Check if color detected is close enough
            if(color_sensor.get_proximity() < 255){
                //Not close enough, just keep running
                intake_top_mtr.move(intakeDirection * INTAKE_TOP_MULTIPLIER * 127);
                continue;
            }

            //Check color, and respond
            if (color_sensor.get_hue() < 50 || color_sensor.get_hue() > 330){
                //Red ring detected, check selected color and respond
                if (color.load() == 0){
                    //Red ring is enabled, keep moving
                    intake_top_mtr.move(intakeDirection * INTAKE_TOP_MULTIPLIER * 127);
                }else{
                    //Blue ring is enabled, expel
                    //Get position, and make target pos round up to nearest multiple of distance between hooks
                    double currentPos = intake_top_mtr.get_position();
                    double targetPos = DISTANCE_BETWEEN_HOOKS * ceil(currentPos / DISTANCE_BETWEEN_HOOKS);
                    double deltaPos = targetPos - currentPos;

                    //Move to target pos
                    while (deltaPos > 10){
                        std::cout << conveyor_pid.update(deltaPos) << std::endl;
                    }
                    pros::delay(1000);
                }
            }else if(color_sensor.get_hue() > 180 && color_sensor.get_hue() < 270){
                //Blue ring, check selected color and respond
                if (color.load() == 1){
                    //Blue ring is enabled, keep moving
                    intake_top_mtr.move(intakeDirection * INTAKE_TOP_MULTIPLIER * 127);
                }else{
                    //Red ring is enabled, expel
                    //Get position, and make target pos round up to nearest multiple of distance between hooks
                    double currentPos = conveyor_encoder.get_position() / 100;
                    double targetPos = DISTANCE_BETWEEN_HOOKS * ceil(currentPos / DISTANCE_BETWEEN_HOOKS);
                    double deltaPos = targetPos - currentPos;;
                    double output = conveyor_pid.update(deltaPos);
                    double startTime = pros::millis();
                    intake_top_mtr.move(0);

                    //Move to target pos
                    while ((deltaPos > 5 || intake_top_mtr.get_actual_velocity() > 5) && pros::millis() - startTime < 4500){
                        intake_top_mtr.move(output);
                        std::cout << currentPos << " " << targetPos << " " << deltaPos << " " << output << std::endl;
                        pros::delay(25);
                        currentPos = conveyor_encoder.get_position() / 100;
                        deltaPos = targetPos - currentPos;
                        output = conveyor_pid.update(deltaPos);
                    }
                    intake_top_mtr.move(0);
                    pros::delay(1000);
                }
            }else{
                //Error color, just keep running
                intake_top_mtr.move(intakeDirection * INTAKE_TOP_MULTIPLIER * 127);
            }
        }else{
            //Sorting not enabled, just run
            intake_top_mtr.move(intakeDirection * INTAKE_TOP_MULTIPLIER * 127);
        }

        //Standard delay
        pros::delay(50);
    }
}
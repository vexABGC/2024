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
    intake_top_mtr.set_zero_position(260);

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

        //Check if normal law
        if (normalLaw){
            //Normal law
            std::cout << color_sensor.get_proximity() << " " << intake_top_mtr.get_position() << std::endl;
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
                    //Raise lady brown if down
                    if (ladyBrownAngle.load() < 40){
                        ladyBrownAngle = 60 * LADY_BROWN_RATIO;
                        intake_top_mtr.move_absolute(intake_top_mtr.get_position(), 200);
                        pros::delay(1000);
                    }
                    
                    //Get position, and make target pos round up to nearest multiple of distance between hooks
                    double currentPos = intake_top_mtr.get_position();
                    double targetPos = DISTANCE_BETWEEN_HOOKS * ceil(currentPos / DISTANCE_BETWEEN_HOOKS);
                    //Move to target pos
                    intake_top_mtr.move_absolute(targetPos, 200);
                    pros::delay(3000);
                }
            }else if(color_sensor.get_hue() > 180 && color_sensor.get_hue() < 270){
                //Blue ring, check selected color and respond
                if (color.load() == 1){
                    //Blue ring is enabled, keep moving
                    intake_top_mtr.move(intakeDirection * INTAKE_TOP_MULTIPLIER * 127);
                }else{
                    //Red ring is enabled, expel
                    //Raise lady brown if down
                    if (ladyBrownAngle.load() < 40){
                        ladyBrownAngle = 60 * LADY_BROWN_RATIO;
                        intake_top_mtr.move_absolute(intake_top_mtr.get_position(), 200);
                        pros::delay(1000);
                    }
                    
                    //Get position, and make target pos round up to nearest multiple of distance between hooks
                    double currentPos = intake_top_mtr.get_position();
                    double targetPos = DISTANCE_BETWEEN_HOOKS * ceil(currentPos / DISTANCE_BETWEEN_HOOKS);
                    //Move to target pos
                    intake_top_mtr.move_absolute(targetPos, 200);
                    pros::delay(3000);
                }
            }else{
                //Error color, just keep running
                intake_top_mtr.move(intakeDirection * INTAKE_TOP_MULTIPLIER * 127);
            }
        }else{
            //Alternative law, just run
            intake_top_mtr.move(intakeDirection * INTAKE_TOP_MULTIPLIER * 127);
        }

        //Standard delay
        pros::delay(50);
    }
}
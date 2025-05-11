//Includes
#include "../src/globals.hpp"
#include "../src/autons/autons.hpp"
#include "../src/control/toInch.hpp"

//Method definition
void line(){
    std::cout<<"Line"<<std::endl;
    lady_brown_mtr.move_absolute(50*5, 60);
    intake_top_mtr.move_relative(-200, 127);
    mogo_piston.retract();
    chassis.odom_xyt_set(toInch(0), toInch(0), 180);
    chassis.pid_odom_set({{toInch(0), toInch(100), 180}, rev, 70});
    chassis.pid_wait();
}
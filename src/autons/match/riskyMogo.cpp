//Includes
#include "../src/globals.hpp"
#include "../src/autons/autons.hpp"
#include "../src/control/toInch.hpp"

//Method definition
void riskyMogo(){
    //Red side
    std::cout<<"Risky Mogo"<<std::endl;
    lady_brown_mtr.move_absolute(50*5, 60);
    intake_top_mtr.move_relative(-200, 127);
    mogo_piston.retract();
    chassis.odom_xyt_set(toInch(135), toInch(-105), 180);
    chassis.pid_odom_set({{toInch(-100), toInch(600), 145}, rev, 70});
    chassis.pid_wait();
    mogo_piston.extend();
    pros::delay(300);
    intake_top_mtr.move(127);
    pros::delay(1500);
    intake_top_mtr.move(0);
    mogo_piston.retract();
    pros::delay(500);
    chassis.pid_turn_set(90, 50);
    chassis.pid_wait();
    intake_bot_mtr.move(-80);
    chassis.pid_odom_set({toInch(400), toInch(600), 90, fwd, 50});
    chassis.pid_wait();
    chassis.pid_turn_set(90, 50);
    chassis.pid_wait();
    chassis.pid_odom_set({toInch(400), toInch(990), 180, rev, 50});
    chassis.pid_wait();
    mogo_piston.extend();
    pros::delay(300);
    intake_top_mtr.move(127);
    intake_bot_mtr.move(0);
    chassis.pid_odom_set({toInch(400), toInch(600), -90, fwd, 90});
    chassis.pid_wait();
    mogo_piston.retract();
    chassis.pid_turn_set(-90, 70);
    chassis.pid_wait();
    chassis.pid_odom_set({toInch(-550), toInch(600), -90, fwd, 90});
    chassis.pid_wait();
    chassis.pid_wait();
}
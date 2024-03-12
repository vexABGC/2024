//includes
#include "main.h"
#include "../src/globals.hpp"

//settings
int deadZone = 10;

//electronics
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor lf_mtr(1, pros::E_MOTOR_GEAR_GREEN, false, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor lb_mtr(2, pros::E_MOTOR_GEAR_GREEN, false, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor rf_mtr(3, pros::E_MOTOR_GEAR_GREEN, false, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor rb_mtr(4, pros::E_MOTOR_GEAR_GREEN, false, pros::E_MOTOR_ENCODER_ROTATIONS);
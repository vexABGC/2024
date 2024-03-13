//includes
#include "main.h"
#include "../src/globals.hpp"

//GUI style/object declarations
lv_style_t rStyle = lv_style_t(); //released button style
lv_style_t pStyle = lv_style_t(); //pressed button style
lv_style_t dStyle = lv_style_t(); //display button style
lv_obj_t* lSelect = lv_btn_create(lv_scr_act(), NULL); //left select button
lv_obj_t* rSelect = lv_btn_create(lv_scr_act(), NULL); //right select button
lv_obj_t* sSelect = lv_btn_create(lv_scr_act(), NULL); //skills select button
lv_obj_t* dSelect = lv_btn_create(lv_scr_act(), NULL); //display select button

//settings
int deadZone = 10;

//electronics
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor lf_mtr(1, pros::E_MOTOR_GEAR_200, false);
pros::Motor lb_mtr(2, pros::E_MOTOR_GEAR_200, false);
pros::Motor rf_mtr(3, pros::E_MOTOR_GEAR_200, false);
pros::Motor rb_mtr(4, pros::E_MOTOR_GEAR_200, false);
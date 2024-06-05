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
int autonomousSelected = 0;
int maxDriveRPM = 0.6 * 600;

//electronics
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor lf_mtr(lf_prt, pros::E_MOTOR_GEAR_600, false);
pros::Motor lb_mtr(lb_prt, pros::E_MOTOR_GEAR_600, false);
pros::Motor rf_mtr(rf_prt, pros::E_MOTOR_GEAR_600, true);
pros::Motor rb_mtr(rb_prt, pros::E_MOTOR_GEAR_600, true);
pros::Motor_Group left_mtrs({lf_mtr, lb_mtr});
pros::Motor_Group right_mtrs({rf_mtr, rb_mtr});
pros::Rotation l_rot(l_rot_prt, false);
pros::Rotation r_rot(r_rot_prt, false);
pros::Imu gyro(gyro_prt);

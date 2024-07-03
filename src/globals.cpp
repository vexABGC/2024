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

//general globals
int autonomousSelected = 0;

//electronics
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor lf_mtr(LF_PRT, pros::E_MOTOR_GEAR_600, false);
pros::Motor lb_mtr(LB_PRT, pros::E_MOTOR_GEAR_600, false);
pros::Motor rf_mtr(RF_PRT, pros::E_MOTOR_GEAR_600, true);
pros::Motor rb_mtr(RB_PRT, pros::E_MOTOR_GEAR_600, true);
pros::Motor strafe_mtr(STRAFE_PRT, pros::E_MOTOR_GEAR_200, true);
pros::Motor_Group left_mtrs({lf_mtr, lb_mtr});
pros::Motor_Group right_mtrs({rf_mtr, rb_mtr});
pros::Rotation l_rot(L_ROT_PRT, false);
pros::Rotation r_rot(R_ROT_PRT, false);
pros::Imu gyro(GYRO_PRT);
pros::ADIDigitalOut mogo_piston(MOGO_PRT);
pros::Motor intake_mtr(INTAKE_PRT, pros::E_MOTOR_GEAR_200, false);
pros::Motor arm_mtr(ARM_PRT, pros::E_MOTOR_GEAR_100, false);
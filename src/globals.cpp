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
lv_obj_t* rActivate = lv_btn_create(lv_scr_act(), NULL); //record activate button
lv_obj_t* replaySelect = lv_btn_create(lv_scr_act(), NULL); //replay select button

//general globals
int autonomousSelected{0};
bool shouldRecord{false};
int mogoVal{0};
double lastLF = 0;
double lastLB = 0;
double lastRF = 0;
double lastRB = 0;
double armAngle = 0;

//electronics
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller partner(pros::E_CONTROLLER_PARTNER);
pros::Motor lf_mtr(LF_PRT, pros::E_MOTOR_GEAR_200, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor lb_mtr(LB_PRT, pros::E_MOTOR_GEAR_200, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rf_mtr(RF_PRT, pros::E_MOTOR_GEAR_200, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rb_mtr(RB_PRT, pros::E_MOTOR_GEAR_200, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor strafe_mtr(STRAFE_PRT, pros::E_MOTOR_GEAR_200, true);
pros::Motor_Group left_mtrs({lf_mtr, lb_mtr});
pros::Motor_Group right_mtrs({rf_mtr, rb_mtr});
pros::Rotation l_rot(L_ROT_PRT, false);
pros::Rotation r_rot(R_ROT_PRT, true);
pros::Imu gyro(GYRO_PRT);
pros::ADIDigitalOut mogo_piston(MOGO_PIS_PRT);
pros::ADIDigitalOut arm_piston(ARM_PIS_PRT);
pros::Motor intake_bot_mtr(INTAKE_BOT_PRT, pros::E_MOTOR_GEAR_200, true);
pros::Motor intake_top_mtr(INTAKE_TOP_PRT, pros::E_MOTOR_GEAR_200, false);
pros::Motor_Group intake_mtrs({intake_bot_mtr, intake_top_mtr});
pros::Motor arm_mtr(ARM_PRT, pros::E_MOTOR_GEAR_100, true);
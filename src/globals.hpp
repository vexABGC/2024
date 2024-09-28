//include
#include "main.h"

//GUI style/object declarations
extern lv_style_t rStyle; //released button style
extern lv_style_t pStyle; //pressed button style
extern lv_style_t dStyle; //display button style
extern lv_obj_t* lSelect; //left select button
extern lv_obj_t* rSelect; //right select button
extern lv_obj_t* sSelect; //skills select button
extern lv_obj_t* dSelect; //display select button
extern lv_obj_t* rActivate; //record activate button
extern lv_obj_t* replaySelect; //replay select button

//general globals
extern int autonomousSelected;
extern bool shouldRecord;
extern int mogoVal;

//settings
#define DEAD_ZONE 10
#define SPEED_MULTIPLIER 0.6
#define ARM_RATIO 1
#define ARM_LOW_ANGLE 0
#define ARM_MID_ANGLE 60
#define ARM_HIGH_ANGLE 120
#define ARM_VELOCITY 60

//ports
#define LF_PRT 13
#define LB_PRT 15
#define RF_PRT 12
#define RB_PRT 14
#define LF_PRT 13
#define LB_PRT 15
#define RF_PRT 12
#define RB_PRT 14
#define STRAFE_PRT 1 // Not installed, placeholder port I don't think we're using
#define L_ROT_PRT 17
#define R_ROT_PRT 11
#define GYRO_PRT 19
#define MOGO_PRT 'H'
#define INTAKE_PRT 16
#define ARM_PRT 18

//electronics
extern pros::Controller master;
extern pros::Controller partner;
extern pros::Motor lf_mtr;
extern pros::Motor lb_mtr;
extern pros::Motor rf_mtr;
extern pros::Motor rb_mtr;
extern pros::Motor strafe_mtr;
extern pros::Motor_Group left_mtrs;
extern pros::Motor_Group right_mtrs;
extern pros::Rotation l_rot;
extern pros::Rotation r_rot;
extern pros::Imu gyro;
extern pros::ADIDigitalOut mogo_piston;
extern pros::Motor intake_mtr;
extern pros::Motor arm_mtr;
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

//general globals
extern int autonomousSelected;

//settings
#define DEAD_ZONE 10
#define SPEED_MULTIPLIER 0.5

//ports
#define LF_PRT 11
#define LB_PRT 14
#define RF_PRT 12
#define RB_PRT 13
#define L_ROT_PRT 1
#define R_ROT_PRT 2
#define GYRO_PRT 6
#define MOGO_PRT 'A'
#define INTAKE_PRT 16

//electronics
extern pros::Controller master;
extern pros::Motor lf_mtr;
extern pros::Motor lb_mtr;
extern pros::Motor rf_mtr;
extern pros::Motor rb_mtr;
extern pros::Motor_Group left_mtrs;
extern pros::Motor_Group right_mtrs;
extern pros::Rotation l_rot;
extern pros::Rotation r_rot;
extern pros::Imu gyro;
extern pros::ADIDigitalOut mogo_piston;
extern pros::Motor intake_mtr;
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
extern double lastLF;
extern double lastLM;
extern double lastLB;
extern double lastRF;
extern double lastRM;
extern double lastRB;

//settings
#define DEAD_ZONE 5
#define SPEED_MULTIPLIER 0.8
#define BRAKE_MULTIPLIER 0.6
#define ARM_RATIO 5
#define ARM_LOW_ANGLE 8.92
#define ARM_MID_ANGLE 80
#define ARM_HIGH_ANGLE 120
#define ARM_VELOCITY_MOVE 60
#define ARM_VELOCITY_BRAKE 20

//ports
#define LF_PRT 19
#define LM_PRT 13
#define LB_PRT 15
#define RF_PRT 11
#define RM_PRT 12
#define RB_PRT 14
#define STRAFE_PRT 10 //Not installed, placeholder port I don't think we're using
#define GYRO_PRT 9 //Note installed, placeholder port I don't think we're using
#define MOGO_PIS_PRT 'H'
#define ARM_PIS_PRT 'G'
#define INTAKE_BOT_PRT 20
#define INTAKE_TOP_PRT 18

//electronics
extern pros::Controller master;
extern pros::Controller partner;
extern pros::Motor lf_mtr;
extern pros::Motor lm_mtr;
extern pros::Motor lb_mtr;
extern pros::Motor rf_mtr;
extern pros::Motor rm_mtr;
extern pros::Motor rb_mtr;
extern pros::Motor strafe_mtr;
extern pros::Motor_Group left_mtrs;
extern pros::Motor_Group right_mtrs;
extern pros::Imu gyro;
extern pros::ADIDigitalOut mogo_piston;
extern pros::ADIDigitalOut arm_piston;
extern pros::Motor intake_top_mtr;
extern pros::Motor intake_bot_mtr;
extern pros::Motor_Group intake_mtrs;
//Include
#include "main.h" // IWYU pragma: keep

//General globals
extern int autonomousSelected;
extern int lastL;
extern int lastR;
extern int mogoVal;
extern int cornerVal;
extern int ladyBrownAngle;

//Settings
#define INPUT_COUNT 300
#define DEAD_ZONE 5
#define SPEED_MULTIPLIER 1
#define BRAKE_MULTIPLIER 0.6
#define LADY_BROWN_RATIO 5
#define LADY_BROWN_LOAD_ANGLE 20
#define LADY_BROWN_SCORE_ANGLE 115
#define LADY_BROWN_MOVE_MULTIPLIER 0.8
#define LADY_BROWN_BRAKE_VELOCITY 100

//Ports
#define LF_PRT 11
#define LM_PRT 12
#define LB_PRT 13
#define RF_PRT 14
#define RM_PRT 15
#define RB_PRT 16
#define INTAKE_TOP_PRT 17
#define INTAKE_BOT_PRT 20
#define LADY_BROWN_PRT 1
#define COLOR_SENSOR_PRT 10
#define V_ENCODER_PRT -9
#define H_ENCODER_PRT 19
#define IMU_PRT 18
#define MOGO_PISTON_PRT 'F'
#define CORNER_PISTON_A_PRT 'G'
#define CORNER_PISTON_B_PRT 'H'

//Electronics
extern pros::Controller master;
extern pros::Controller partner;
extern pros::MotorGroup left_mtrs;
extern pros::MotorGroup right_mtrs;
extern pros::Motor intake_top_mtr;
extern pros::Motor intake_bot_mtr;
extern pros::Motor lady_brown_mtr;
extern pros::adi::Pneumatics mogo_piston;
extern pros::adi::Pneumatics corner_piston_a;
extern pros::adi::Pneumatics corner_piston_b;

//Chassis
extern ez::Drive chassis;
extern ez::tracking_wheel v_tracker;
extern ez::tracking_wheel h_tracker;
//Include
#include "main.h" // IWYU pragma: keep
#include <atomic>

//GUI style/object declarations
extern lv_style_t main_page_style;
extern lv_style_t motor_page_style;
extern lv_style_t record_button_style;
extern lv_style_t replay_button_style;
extern lv_style_t location_button_style_rel;
extern lv_style_t location_button_style_pr;
extern lv_style_t skills_button_style_pr;
extern lv_obj_t* main_page;
extern lv_obj_t* motor_page;
extern lv_obj_t* main_page_button;
extern lv_obj_t* motor_page_button;
extern lv_obj_t* record_button;
extern lv_obj_t* record_text;
extern lv_obj_t* replay_button;
extern lv_obj_t* replay_text;
extern lv_obj_t* map_image;
extern lv_obj_t* lr_button;
extern lv_obj_t* rb_button;
extern lv_obj_t* rr_button;
extern lv_obj_t* lb_button;
extern lv_obj_t* skills_button;

//General globals
extern int autonomousSelected;
extern bool shouldRecord;
extern int lastL;
extern int lastR;
extern int mogoVal;
extern int cornerVal;
extern std::atomic<int> ladyBrownAngle;
extern std::atomic<int> color;
extern std::atomic<bool> normalLaw;
extern std::atomic<double> intakeDirection;

//Settings
#define INPUT_COUNT 300
#define DEAD_ZONE 5
#define SPEED_MULTIPLIER 1
#define BRAKE_MULTIPLIER 0.6
#define INTAKE_TOP_MULTIPLIER 1
#define DISTANCE_BETWEEN_HOOKS 563.972
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
#define INTAKE_BOT_PRT 18
#define LADY_BROWN_PRT 7
#define COLOR_SENSOR_PRT 10
#define V_ENCODER_PRT 20
#define H_ENCODER_PRT 8
#define IMU_PRT 19
#define MOGO_PISTON_PRT 'A'
#define CORNER_PISTON_A_PRT 'B'
#define CORNER_PISTON_B_PRT 'C'

//Electronics
extern pros::Controller master;
extern pros::Controller partner;
extern pros::MotorGroup left_mtrs;
extern pros::MotorGroup right_mtrs;
extern pros::Motor intake_top_mtr;
extern pros::Motor intake_bot_mtr;
extern pros::Motor lady_brown_mtr;
extern pros::Optical color_sensor;
extern pros::Rotation v_encoder;
extern pros::Rotation h_encoder;
extern pros::Imu imu;
extern pros::adi::Pneumatics mogo_piston;
extern pros::adi::Pneumatics corner_piston_a;
extern pros::adi::Pneumatics corner_piston_b;

//Setup drive PID
extern lemlib::ControllerSettings lateral_controller;
extern lemlib::ControllerSettings angular_controller;

//Setup drive train, sensors, and chassis
extern lemlib::Drivetrain drive_train;
extern lemlib::TrackingWheel v_tracking_wheel;
extern lemlib::TrackingWheel h_tracking_wheel;
extern lemlib::OdomSensors sensors;
extern lemlib::Chassis chassis;
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
extern int mogoVal;
extern double lastLF;
extern double lastLM;
extern double lastLB;
extern double lastRF;
extern double lastRM;
extern double lastRB;
extern int cornerAngle;
extern std::atomic<int> color;
extern std::atomic<bool> sortingEnabled;
extern std::atomic<int> intakeDirection;

//Settings
#define INPUT_COUNT 300
#define DEAD_ZONE 5
#define SPEED_MULTIPLIER 0.8
#define BRAKE_MULTIPLIER 0.6
#define INTAKE_TOP_MULTIPLIER 1
#define ARM_RATIO 5
#define ARM_LOW_ANGLE 8.92
#define ARM_MID_ANGLE 80
#define ARM_HIGH_ANGLE 120
#define ARM_VELOCITY_MOVE 60
#define ARM_VELOCITY_BRAKE 20

//Ports
#define LF_PRT 10
#define LM_PRT 9
#define LB_PRT 8
#define RF_PRT 7
#define RM_PRT 6
#define RB_PRT 5
#define INTAKE_TOP_PRT 4
#define INTAKE_BOT_PRT 3
#define CORNER_PRT 2
#define COLOR_SENSOR_PRT 1
#define LV_ENCODER_PRT 11
#define RV_ENCODER_PRT 12
#define IMU_PRT 13
#define MOGO_PISTON_PRT 'A'

//Electronics
extern pros::Controller master;
extern pros::Controller partner;
extern pros::Motor lf_mtr;
extern pros::Motor lm_mtr;
extern pros::Motor lb_mtr;
extern pros::Motor rf_mtr;
extern pros::Motor rm_mtr;
extern pros::Motor rb_mtr;
extern pros::Motor_Group left_mtrs;
extern pros::Motor_Group right_mtrs;
extern pros::Motor intake_top_mtr;
extern pros::Motor intake_bot_mtr;
extern pros::Motor_Group intake_mtrs;
extern pros::Motor corner_mtr;
extern pros::Optical color_sensor;
extern pros::Rotation lv_encoder;
extern pros::Rotation rv_encoder;
extern pros::Imu imu;
extern pros::ADIDigitalOut mogo_piston;

//Setup PID
extern lemlib::ControllerSettings lateral_controller;
extern lemlib::ControllerSettings angular_controller;

//Setup drive train, sensors, and chassis
extern lemlib::Drivetrain drive_train;
extern lemlib::TrackingWheel lv_tracking_wheel;
extern lemlib::TrackingWheel rv_tracking_wheel;
extern lemlib::OdomSensors sensors;
extern lemlib::Chassis chassis;
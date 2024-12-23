//includes
#include "lemlib/api.hpp"
#include "main.h"
#include "../src/globals.hpp"
#include <atomic>
#include <memory>


//GUI style/object declarations
lv_style_t main_page_style;
lv_style_t motor_page_style;
lv_style_t record_button_style;
lv_style_t replay_button_style;
lv_style_t location_button_style_rel;
lv_style_t location_button_style_pr;
lv_style_t skills_button_style_pr;
lv_obj_t* main_page;
lv_obj_t* motor_page;
lv_obj_t* main_page_button;
lv_obj_t* motor_page_button;
lv_obj_t* record_button;
lv_obj_t* record_text;
lv_obj_t* replay_button;
lv_obj_t* replay_text;
lv_obj_t* map_image;
lv_obj_t* lr_button;
lv_obj_t* rb_button;
lv_obj_t* rr_button;
lv_obj_t* lb_button;
lv_obj_t* skills_button;

//general globals
int autonomousSelected{0};
bool shouldRecord{false};
int mogoVal{0};
double lastLF = 0;
double lastLM = 0;
double lastLB = 0;
double lastRF = 0;
double lastRM = 0;
double lastRB = 0;
int cornerAngle = 0;
int color = 0;
std::atomic<bool> sortingEnabled = true;
std::atomic<int> intakeTopAmount = 0;
pros::Task intakeThread = NULL;

//electronics
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller partner(pros::E_CONTROLLER_PARTNER);
pros::Motor lf_mtr(LF_PRT, pros::E_MOTOR_GEAR_200, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor lm_mtr(LM_PRT, pros::E_MOTOR_GEAR_200, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor lb_mtr(LB_PRT, pros::E_MOTOR_GEAR_200, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rf_mtr(RF_PRT, pros::E_MOTOR_GEAR_200, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rm_mtr(RM_PRT, pros::E_MOTOR_GEAR_200, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rb_mtr(RB_PRT, pros::E_MOTOR_GEAR_200, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor_Group left_mtrs({lf_mtr, lm_mtr, lb_mtr});
pros::Motor_Group right_mtrs({rf_mtr, rm_mtr, rb_mtr});
pros::Motor intake_top_mtr(INTAKE_TOP_PRT, pros::E_MOTOR_GEAR_600, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor intake_bot_mtr(INTAKE_BOT_PRT, pros::E_MOTOR_GEAR_200, true, pros::E_MOTOR_ENCODER_DEGREES); 
pros::Motor_Group intake_mtrs({intake_top_mtr, intake_bot_mtr});
pros::Motor corner_mtr(CORNER_PRT, pros::E_MOTOR_GEAR_200, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Optical color_sensor(COLOR_SENSOR_PRT);
pros::Rotation v_encoder(V_ENCODER_PRT);
pros::Rotation h_encoder(H_ENCODER_PRT);
pros::Imu imu(IMU_PRT);
pros::ADIDigitalOut mogo_piston(MOGO_PISTON_PRT);

//setup PID
//KP   - proportional gain
//KI   - integral gain
//KD   - derivative gain
//AW   - Anti Windup
//SE   - Small Error
//SET  - Small Error Timeout
//LE   - Large Error
//LET  - Large Error Timeout
//SLEW - Acceleration                        KP, KI, KD, AW, SE, SET, LE, LET, SLEW
lemlib::ControllerSettings lateral_controller(10, 0 , 3 , 3 , 1 , 100, 3 , 500, 20  );
lemlib::ControllerSettings angular_controller(2 , 0 , 10, 3 , 1 , 100, 3 , 500, 0   );

//setup drive train, sensors, and chassis
lemlib::Drivetrain drive_train(&left_mtrs, &right_mtrs, 15.25, 3.25, 450, 8);
lemlib::TrackingWheel v_tracking_wheel(&v_encoder, 3.25, 0);
lemlib::TrackingWheel h_tracking_wheel(&h_encoder, 3.25, 0);
lemlib::OdomSensors sensors(&v_tracking_wheel, nullptr, &h_tracking_wheel, nullptr, &imu);
lemlib::Chassis chassis(drive_train, lateral_controller, angular_controller, sensors);
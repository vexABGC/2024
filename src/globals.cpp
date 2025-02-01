//Includes
#include "main.h" // IWYU pragma: keep
#include "pros/abstract_motor.hpp"
#include "pros/adi.hpp"
#include "../src/globals.hpp"
#include <atomic>


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

//General globals
int autonomousSelected{0};
bool shouldRecord{false};
int lastL{0};
int lastR{0};
int mogoVal{0};
int cornerVal{0};
std::atomic<int> ladyBrownAngle{0};
std::atomic<int> color = 0;
std::atomic<bool> normalLaw = true;
std::atomic<double> intakeDirection = 1;

//Electronics
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller partner(pros::E_CONTROLLER_PARTNER);
pros::MotorGroup left_mtrs({LF_PRT, -LM_PRT, -LB_PRT}, pros::v5::MotorGears::rpm_600, pros::v5::MotorUnits::degrees);
pros::MotorGroup right_mtrs({-RF_PRT, RM_PRT, RB_PRT}, pros::v5::MotorGears::rpm_600, pros::v5::MotorUnits::degrees);
pros::Motor intake_top_mtr(-INTAKE_TOP_PRT, pros::v5::MotorGears::rpm_200, pros::v5::MotorUnits::degrees);
pros::Motor intake_bot_mtr(-INTAKE_BOT_PRT, pros::v5::MotorGears::rpm_200, pros::v5::MotorUnits::degrees);
pros::Motor lady_brown_mtr(LADY_BROWN_PRT, pros::v5::MotorGears::rpm_200, pros::v5::MotorUnits::degrees);
pros::Optical color_sensor(COLOR_SENSOR_PRT);
pros::Rotation v_encoder(V_ENCODER_PRT);
pros::Rotation h_encoder(H_ENCODER_PRT);
pros::Imu imu(IMU_PRT);
pros::adi::Pneumatics mogo_piston(MOGO_PISTON_PRT, false);
pros::adi::Pneumatics corner_piston_a(CORNER_PISTON_A_PRT, false);
pros::adi::Pneumatics corner_piston_b(CORNER_PISTON_B_PRT, false);

//Setup drive PID
lemlib::ControllerSettings lateral_controller(4.5, 0, 6, 3, 1, 10, 3, 500, 20);
lemlib::ControllerSettings angular_controller(3.25, 0, 23.5, 3, 1, 100, 3, 500, 0);

//Setup drive train, sensors, and chassis
lemlib::Drivetrain drive_train(&left_mtrs, &right_mtrs, 15.25, 3.25, 450, 8);
lemlib::TrackingWheel v_tracking_wheel(&v_encoder, 3.25, -1.8);
lemlib::TrackingWheel h_tracking_wheel(&h_encoder, 3.25, 1);
lemlib::OdomSensors sensors(&v_tracking_wheel, nullptr , &h_tracking_wheel, nullptr, &imu);
lemlib::Chassis chassis(drive_train, lateral_controller, angular_controller, sensors);
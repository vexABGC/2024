//Includes
#include "EZ-Template/drive/drive.hpp"
#include "EZ-Template/tracking_wheel.hpp"
#include "main.h" // IWYU pragma: keep
#include "../src/globals.hpp"

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
int ladyBrownAngle{0};

//Electronics
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller partner(pros::E_CONTROLLER_PARTNER);
pros::MotorGroup left_mtrs({LF_PRT, -LM_PRT, -LB_PRT}, pros::v5::MotorGears::rpm_600, pros::v5::MotorUnits::degrees);
pros::MotorGroup right_mtrs({-RF_PRT, RM_PRT, RB_PRT}, pros::v5::MotorGears::rpm_600, pros::v5::MotorUnits::degrees);
pros::Motor intake_top_mtr(-INTAKE_TOP_PRT, pros::v5::MotorGears::rpm_200, pros::v5::MotorUnits::degrees);
pros::Motor intake_bot_mtr(-INTAKE_BOT_PRT, pros::v5::MotorGears::rpm_200, pros::v5::MotorUnits::degrees);
pros::Motor lady_brown_mtr(LADY_BROWN_PRT, pros::v5::MotorGears::rpm_200, pros::v5::MotorUnits::degrees);
pros::adi::Pneumatics mogo_piston(MOGO_PISTON_PRT, false);
pros::adi::Pneumatics corner_piston_a(CORNER_PISTON_A_PRT, false);
pros::adi::Pneumatics corner_piston_b(CORNER_PISTON_B_PRT, false);

//Chassis
ez::Drive chassis(
    {LF_PRT, -LM_PRT, -LB_PRT}, //Left drive ports
    {-RF_PRT, RM_PRT, RB_PRT}, //Right drive ports
    IMU_PRT, //IMU port
    3.25, //Wheel diameter
    450 //Drive RPM
);
ez::tracking_wheel v_tracker(V_ENCODER_PRT, 3.25, -1.8);
ez::tracking_wheel h_tracker(H_ENCODER_PRT, 3.25, 1);
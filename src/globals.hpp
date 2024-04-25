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

//settings
extern int deadZone;
extern int autonomousSelected;
extern int maxDriveRPM;

//electronics
extern pros::Controller master;
extern pros::Motor lf_mtr;
extern pros::Motor lb_mtr;
extern pros::Motor rf_mtr;
extern pros::Motor rb_mtr;
extern pros::Rotation l_rot;
extern pros::Rotation r_rot;
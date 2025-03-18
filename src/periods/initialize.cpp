//Includes
#include "main.h"
#include "../src/globals.hpp"
#include "../src/control/buttonMethod.hpp"
#include "../src/control/controllerScreen.hpp"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    //Calibrate
    chassis.odom_tracker_left_set(&v_tracker);
    chassis.odom_tracker_front_set(&h_tracker);
    chassis.initialize();
    
    //GUI Setup
    //Setup main page
    main_page_style = lv_style_t();
    lv_style_copy(&main_page_style, &lv_style_plain);
    main_page_style.body.main_color = LV_COLOR_BLACK;
    main_page_style.body.grad_color = LV_COLOR_BLACK;
    main_page_style.body.padding.ver = 0;
    main_page_style.body.padding.hor = 0;
    main_page = lv_page_create(lv_scr_act(), NULL);
    lv_obj_set_size(main_page, 480, 240);
    lv_obj_set_pos(main_page, 0, 0);
    lv_obj_set_style(main_page, &main_page_style);
    lv_page_set_sb_mode(main_page, LV_SB_MODE_OFF);
    lv_obj_t* fakeButtonMain = lv_btn_create(main_page, NULL);
    lv_btn_set_style(fakeButtonMain, LV_BTN_STYLE_REL, &lv_style_transp);
    lv_btn_set_style(fakeButtonMain, LV_BTN_STYLE_PR, &lv_style_transp);

    //Setup motor page
    motor_page_style = lv_style_t();
    lv_style_copy(&motor_page_style, &lv_style_plain);
    motor_page_style.body.main_color = LV_COLOR_BLACK;
    motor_page_style.body.grad_color = LV_COLOR_BLACK;
    motor_page_style.body.padding.ver = 0;
    motor_page_style.body.padding.hor = 0;
    motor_page = lv_page_create(lv_scr_act(), NULL);
    lv_obj_set_size(motor_page, 480, 240);
    lv_obj_set_pos(motor_page, 0, 0);
    lv_obj_set_style(motor_page, &main_page_style);
    lv_page_set_sb_mode(motor_page, LV_SB_MODE_OFF);
    lv_btn_set_style(lv_btn_create(motor_page, NULL), LV_BTN_STYLE_REL, &lv_style_transp);
    lv_obj_t* fakeButtonMotor = lv_btn_create(motor_page, NULL);
    lv_btn_set_style(fakeButtonMotor, LV_BTN_STYLE_REL, &lv_style_transp);
    lv_btn_set_style(fakeButtonMotor, LV_BTN_STYLE_PR, &lv_style_transp);
    lv_obj_set_hidden(motor_page, true);

    //Setup main page content
    //Menu button
    main_page_button = lv_imgbtn_create(lv_scr_act(), NULL);
    LV_IMG_DECLARE(logo);
    lv_obj_set_size(main_page_button, 80, 80);
    lv_obj_set_pos(main_page_button, 313, 10);
    lv_imgbtn_set_src(main_page_button, LV_BTN_STATE_REL, &logo);
    lv_imgbtn_set_src(main_page_button, LV_BTN_STATE_PR, &logo);
    lv_obj_set_free_num(main_page_button, 0);
    lv_imgbtn_set_action(main_page_button, LV_BTN_ACTION_CLICK, buttonMethod);

    //Record/replay buttons
    record_button_style = lv_style_t();
    lv_style_copy(&record_button_style, &lv_style_plain);
    record_button_style.body.main_color = LV_COLOR_BLACK;
    record_button_style.body.grad_color = LV_COLOR_BLACK;
    record_button_style.body.border.color = LV_COLOR_WHITE;
    record_button_style.text.color = LV_COLOR_WHITE;
    record_button_style.body.radius = 10;
    record_button_style.body.border.width = 3;
    record_button = lv_btn_create(main_page, NULL);
    lv_btn_set_style(record_button, LV_BTN_STYLE_REL, &record_button_style);
    lv_btn_set_style(record_button, LV_BTN_STYLE_PR, &record_button_style);
    lv_obj_set_size(record_button, 192, 50);
    lv_obj_set_pos(record_button, 264, 100);
    record_text = lv_label_create(record_button, NULL);
    lv_label_set_text(record_text, "Record");
    lv_obj_set_free_num(record_button, 1);
    lv_btn_set_action(record_button, LV_BTN_ACTION_CLICK, buttonMethod);
    replay_button_style = lv_style_t();
    lv_style_copy(&replay_button_style, &lv_style_plain);
    replay_button_style.body.main_color = LV_COLOR_BLACK;
    replay_button_style.body.grad_color = LV_COLOR_BLACK;
    replay_button_style.body.border.color = LV_COLOR_WHITE;
    replay_button_style.text.color = LV_COLOR_WHITE;
    replay_button_style.body.radius = 10;
    replay_button_style.body.border.width = 3;
    replay_button = lv_btn_create(main_page, NULL);
    lv_btn_set_style(replay_button, LV_BTN_STYLE_REL, &replay_button_style);
    lv_btn_set_style(replay_button, LV_BTN_STYLE_PR, &replay_button_style);
    lv_obj_set_size(replay_button, 192, 50);
    lv_obj_set_pos(replay_button, 264, 160);
    replay_text = lv_label_create(replay_button, NULL);
    lv_label_set_text(replay_text, "Replay");
    lv_obj_set_free_num(replay_button, 2);
    lv_btn_set_action(replay_button, LV_BTN_ACTION_CLICK, buttonMethod);

    //Map buttons
    //Style
    location_button_style_rel = lv_style_t();
    location_button_style_rel.body.opa = 0;
    location_button_style_rel.body.border.width = 0;
    location_button_style_pr = lv_style_t();
    location_button_style_pr.body.opa = 80;
    location_button_style_pr.body.main_color = LV_COLOR_GREEN;
    location_button_style_pr.body.grad_color = LV_COLOR_GREEN;
    location_button_style_pr.body.border.width = 0;
    skills_button_style_pr = lv_style_t();
    skills_button_style_pr.body.opa = 80;
    skills_button_style_pr.body.main_color = LV_COLOR_PURPLE;
    skills_button_style_pr.body.grad_color = LV_COLOR_PURPLE;
    skills_button_style_pr.body.border.width = 0;
    //Image
    map_image = lv_img_create(main_page, NULL);
    LV_IMG_DECLARE(field_regular);
    lv_img_set_src(map_image, &field_regular);
    //left red (top left)
    lr_button = lv_btn_create(main_page, NULL);
    lv_obj_set_pos(lr_button, 0, 0);
    lv_obj_set_size(lr_button, 120, 120);
    lv_btn_set_style(lr_button, LV_BTN_STYLE_REL, &location_button_style_pr);
    lv_btn_set_style(lr_button, LV_BTN_STYLE_PR, &location_button_style_pr);
    lv_obj_set_free_num(lr_button, 3);
    lv_btn_set_action(lr_button, LV_BTN_ACTION_CLICK, buttonMethod);
    //right blue (top right)
    rb_button = lv_btn_create(main_page, NULL);
    lv_obj_set_pos(rb_button, 120, 0);
    lv_obj_set_size(rb_button, 120, 120);
    lv_btn_set_style(rb_button, LV_BTN_STYLE_REL, &location_button_style_rel);
    lv_btn_set_style(rb_button, LV_BTN_STYLE_PR, &location_button_style_pr);
    lv_obj_set_free_num(rb_button, 4);
    lv_btn_set_action(rb_button, LV_BTN_ACTION_CLICK, buttonMethod);
    //right red (bottom left)
    rr_button = lv_btn_create(main_page, NULL);
    lv_obj_set_pos(rr_button, 0, 120);
    lv_obj_set_size(rr_button, 120, 120);
    lv_btn_set_style(rr_button, LV_BTN_STYLE_REL, &location_button_style_rel);
    lv_btn_set_style(rr_button, LV_BTN_STYLE_PR, &location_button_style_pr);
    lv_obj_set_free_num(rr_button, 5);
    lv_btn_set_action(rr_button, LV_BTN_ACTION_CLICK, buttonMethod);
    //left blue (bottom right)
    lb_button = lv_btn_create(main_page, NULL);
    lv_obj_set_pos(lb_button, 120, 120);
    lv_obj_set_size(lb_button, 120, 120);
    lv_btn_set_style(lb_button, LV_BTN_STYLE_REL, &location_button_style_rel);
    lv_btn_set_style(lb_button, LV_BTN_STYLE_PR, &location_button_style_pr);
    lv_obj_set_free_num(lb_button, 6);
    lv_btn_set_action(lb_button, LV_BTN_ACTION_CLICK, buttonMethod);
    //skills (middle diagonal)
    skills_button = lv_btn_create(main_page, NULL);
    lv_obj_set_pos(skills_button, 80, 80);
    lv_obj_set_size(skills_button, 80, 80);
    lv_btn_set_style(skills_button, LV_BTN_STYLE_REL, &location_button_style_rel);
    lv_btn_set_style(skills_button, LV_BTN_STYLE_PR, &skills_button_style_pr);
    lv_obj_set_free_num(skills_button, 7);
    lv_btn_set_action(skills_button, LV_BTN_ACTION_CLICK, buttonMethod);

    //Lady brown setup
    lady_brown_mtr.tare_position();
    ladyBrownAngle = 0;
}
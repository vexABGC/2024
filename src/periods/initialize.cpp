//includes
#include "main.h"
#include "../src/globals.hpp"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    //GUI Setup
    //released button style
    lv_style_copy(&rStyle, &lv_style_plain);
    rStyle.body.main_color = LV_COLOR_MAKE(50, 168, 82);
    rStyle.body.grad_color = LV_COLOR_MAKE(82, 168, 50);
    rStyle.body.radius = 0;
    rStyle.text.color = LV_COLOR_MAKE(255,255,255);

    //pressed button style
    lv_style_copy(&pStyle, &lv_style_plain);
    pStyle.body.main_color = LV_COLOR_MAKE(25, 84, 41);
    pStyle.body.grad_color = LV_COLOR_MAKE(41, 84, 25);
    pStyle.body.radius = 0;
    pStyle.text.color = LV_COLOR_MAKE(255,255,255);

    //display button style
    lv_style_copy(&dStyle, &lv_style_plain);
    dStyle.body.main_color = LV_COLOR_MAKE(255, 255, 255);
    dStyle.body.grad_color = LV_COLOR_MAKE(127, 127, 127);
    dStyle.body.radius = 0;
    dStyle.text.color = LV_COLOR_MAKE(0, 0, 0);

    lv_obj_set_free_num(lSelect, 0);
    //lv_btn_set_action(lSelect, LV_BTN_ACTION_CLICK, );
    lv_btn_set_style(lSelect, LV_BTN_STYLE_REL, &rStyle);
    lv_btn_set_style(lSelect, LV_BTN_STYLE_PR, &pStyle);
    lv_obj_set_size(lSelect, 150, 70);
    lv_obj_align(lSelect, NULL, LV_ALIGN_IN_TOP_LEFT, 7.5, 5);
    lv_label_set_text(lv_label_create(lSelect, NULL), "left");

    lv_obj_set_free_num(rSelect, 1);
    //lv_btn_set_action(rSelect, LV_BTN_ACTION_CLICK, );
    lv_btn_set_style(rSelect, LV_BTN_STYLE_REL, &rStyle);
    lv_btn_set_style(rSelect, LV_BTN_STYLE_PR, &pStyle);
    lv_obj_set_size(rSelect, 150, 70);
    lv_obj_align(rSelect, NULL, LV_ALIGN_IN_TOP_RIGHT, -7.5, 5);
    lv_label_set_text(lv_label_create(rSelect, NULL), "right");

    lv_obj_set_free_num(sSelect, 2);
    //lv_btn_set_action(sSelect, LV_BTN_ACTION_CLICK, );
    lv_btn_set_style(sSelect, LV_BTN_STYLE_REL, &rStyle);
    lv_btn_set_style(sSelect, LV_BTN_STYLE_PR, &pStyle);
    lv_obj_set_size(sSelect, 150, 70);
    lv_obj_align(sSelect, NULL, LV_ALIGN_IN_TOP_MID, 0, 5);
    lv_label_set_text(lv_label_create(sSelect, NULL), "skills");

    lv_obj_set_free_num(dSelect, 3);
    //lv_btn_set_action(dSelect, LV_BTN_ACTION_CLICK, );
    lv_btn_set_style(dSelect, LV_BTN_STYLE_REL, &dStyle);
    lv_btn_set_style(dSelect, LV_BTN_STYLE_PR, &dStyle);
    lv_obj_set_size(dSelect, 465, 150);
    lv_obj_align(dSelect, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -5);
    lv_label_set_text(lv_label_create(dSelect, NULL), "left");
}
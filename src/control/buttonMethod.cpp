//Includes
#include "../src/control/buttonMethod.hpp"
#include "../src/globals.hpp"
#include "../src/control/controllerScreen.hpp"

//Method definition
lv_res_t buttonMethod(lv_obj_t* btn){
	int id = lv_obj_get_free_num(btn);
    std::cout << id << std::endl;
    switch (id){
        case 0:
            //Menu button
            lv_obj_set_hidden(main_page, !lv_obj_get_hidden(main_page));
            lv_obj_set_hidden(motor_page, !lv_obj_get_hidden(motor_page));
            break;
        case 1:
            //Record
            replay_button_style.body.main_color = LV_COLOR_GREEN;
            replay_button_style.body.grad_color = LV_COLOR_GREEN;
            lv_btn_set_style(replay_button, LV_BTN_STYLE_REL, &replay_button_style);
            record_button_style.body.main_color = LV_COLOR_RED;
            record_button_style.body.grad_color = LV_COLOR_RED;
            lv_btn_set_style(record_button, LV_BTN_STYLE_REL, &record_button_style);
            lv_btn_set_style(lr_button, LV_BTN_STYLE_REL, &location_button_style_rel);
            lv_btn_set_style(rb_button, LV_BTN_STYLE_REL, &location_button_style_rel);
            lv_btn_set_style(rr_button, LV_BTN_STYLE_REL, &location_button_style_rel);
            lv_btn_set_style(lb_button, LV_BTN_STYLE_REL, &location_button_style_rel);
            lv_btn_set_style(skills_button, LV_BTN_STYLE_REL, &location_button_style_rel);
            shouldRecord = true;
            autonomousSelected = 5;
            break;
        case 2:
            //Replay
            replay_button_style.body.main_color = LV_COLOR_GREEN;
            replay_button_style.body.grad_color = LV_COLOR_GREEN;
            lv_btn_set_style(lr_button, LV_BTN_STYLE_REL, &location_button_style_rel);
            lv_btn_set_style(rb_button, LV_BTN_STYLE_REL, &location_button_style_rel);
            lv_btn_set_style(rr_button, LV_BTN_STYLE_REL, &location_button_style_rel);
            lv_btn_set_style(lb_button, LV_BTN_STYLE_REL, &location_button_style_rel);
            lv_btn_set_style(skills_button, LV_BTN_STYLE_REL, &location_button_style_rel);
            autonomousSelected = 5;
            break;
        case 3:
            //Left red
            //Set styles of selectors
            if (lv_btn_get_style(lr_button, LV_BTN_STYLE_REL)->body.opa == location_button_style_pr.body.opa){
                //Disable
                LV_IMG_DECLARE(red_x_regular);
                lv_img_set_src(map_image, &red_x_regular);
                lv_btn_set_style(lr_button, LV_BTN_STYLE_REL, &location_button_style_rel);
                raiseControllerWarning("Autonomous Disabled");
                autonomousSelected = 6;
                sortingEnabled = 0;
            }else{
                //Regular
                color = 0;
                sortingEnabled = 1;
                lv_btn_set_style(lr_button, LV_BTN_STYLE_REL, &location_button_style_pr);
                raiseControllerWarning("Auton left red");
                LV_IMG_DECLARE(field_regular);
                lv_img_set_src(map_image, &field_regular);
            }
            lv_btn_set_style(rb_button, LV_BTN_STYLE_REL, &location_button_style_rel);
            lv_btn_set_style(rr_button, LV_BTN_STYLE_REL, &location_button_style_rel);
            lv_btn_set_style(lb_button, LV_BTN_STYLE_REL, &location_button_style_rel);
            replay_button_style.body.main_color = LV_COLOR_BLACK;
            replay_button_style.body.grad_color = LV_COLOR_BLACK;
            lv_btn_set_style(replay_button, LV_BTN_STYLE_REL, &replay_button_style);
            //Change auton selector
            autonomousSelected = 0;
            break;
        case 4:
            //Right blue
            //Set styles of selectors
            if (lv_btn_get_style(rb_button, LV_BTN_STYLE_REL)->body.opa == location_button_style_pr.body.opa){
                //Disable
                LV_IMG_DECLARE(red_x_regular);
                lv_img_set_src(map_image, &red_x_regular);
                lv_btn_set_style(rb_button, LV_BTN_STYLE_REL, &location_button_style_rel); 
                lv_btn_set_style(skills_button, LV_BTN_STYLE_REL, &location_button_style_rel);
                raiseControllerWarning("Auton disabled");
                autonomousSelected = 6;
                sortingEnabled = 0;
            }else{
                //Regular
                color = 1;
                sortingEnabled = 1;
                lv_btn_set_style(rb_button, LV_BTN_STYLE_REL, &location_button_style_pr);
                raiseControllerWarning("Auton right blue");
                LV_IMG_DECLARE(field_regular);
                lv_img_set_src(map_image, &field_regular);
            }
            lv_btn_set_style(lr_button, LV_BTN_STYLE_REL, &location_button_style_rel);
            lv_btn_set_style(rr_button, LV_BTN_STYLE_REL, &location_button_style_rel);
            lv_btn_set_style(lb_button, LV_BTN_STYLE_REL, &location_button_style_rel);
            lv_btn_set_style(skills_button, LV_BTN_STYLE_REL, &location_button_style_rel);
            replay_button_style.body.main_color = LV_COLOR_BLACK;
            replay_button_style.body.grad_color = LV_COLOR_BLACK;
            lv_btn_set_style(replay_button, LV_BTN_STYLE_REL, &replay_button_style);
            //Change auton selector
            autonomousSelected = 1;
            break;
        case 5:
            //Right red
            //Set styles of selectors
            if (lv_btn_get_style(rr_button, LV_BTN_STYLE_REL)->body.opa == location_button_style_pr.body.opa){
                //Disable
                LV_IMG_DECLARE(red_x_regular);
                lv_img_set_src(map_image, &red_x_regular);
                lv_btn_set_style(rr_button, LV_BTN_STYLE_REL, &location_button_style_rel); 
                raiseControllerWarning("Auton disabled");  
                autonomousSelected = 6;
                sortingEnabled = 0;
            }else{
                //Regular
                color = 0;
                sortingEnabled = 1;
                lv_btn_set_style(rr_button, LV_BTN_STYLE_REL, &location_button_style_pr);
                raiseControllerWarning("Auton right red");
                LV_IMG_DECLARE(field_regular);
                lv_img_set_src(map_image, &field_regular);
            }
            lv_btn_set_style(lr_button, LV_BTN_STYLE_REL, &location_button_style_rel);
            lv_btn_set_style(rb_button, LV_BTN_STYLE_REL, &location_button_style_rel);
            lv_btn_set_style(lb_button, LV_BTN_STYLE_REL, &location_button_style_rel);
            lv_btn_set_style(skills_button, LV_BTN_STYLE_REL, &location_button_style_rel);
            replay_button_style.body.main_color = LV_COLOR_BLACK;
            replay_button_style.body.grad_color = LV_COLOR_BLACK;
            lv_btn_set_style(replay_button, LV_BTN_STYLE_REL, &replay_button_style);
            //Change auton selector
            autonomousSelected = 2;
            break;
        case 6:
            //Left blue
            //Set styles of selectors
            if (lv_btn_get_style(lb_button, LV_BTN_STYLE_REL)->body.opa == location_button_style_pr.body.opa){
                //Disable
                LV_IMG_DECLARE(red_x_regular);
                lv_img_set_src(map_image, &red_x_regular);
                lv_btn_set_style(lb_button, LV_BTN_STYLE_REL, &location_button_style_rel); 
                raiseControllerWarning("Auton disabled");
                autonomousSelected = 6;
                sortingEnabled = 0;
            }else{
                //Regular
                color = 1;
                sortingEnabled = 1;
                lv_btn_set_style(lb_button, LV_BTN_STYLE_REL, &location_button_style_pr);
                raiseControllerWarning("Auton left blue");
                LV_IMG_DECLARE(field_regular);
                lv_img_set_src(map_image, &field_regular);
            }
            lv_btn_set_style(lr_button, LV_BTN_STYLE_REL, &location_button_style_rel);
            lv_btn_set_style(rb_button, LV_BTN_STYLE_REL, &location_button_style_rel);
            lv_btn_set_style(rr_button, LV_BTN_STYLE_REL, &location_button_style_rel);
            lv_btn_set_style(skills_button, LV_BTN_STYLE_REL, &location_button_style_rel);
            replay_button_style.body.main_color = LV_COLOR_BLACK;
            replay_button_style.body.grad_color = LV_COLOR_BLACK;
            lv_btn_set_style(replay_button, LV_BTN_STYLE_REL, &replay_button_style);
            //Change auton selector
            autonomousSelected = 3;
            break;
        case 7:
            //Skills
            //Set styles of selectors
            if (lv_btn_get_style(skills_button, LV_BTN_STYLE_REL)->body.opa == location_button_style_pr.body.opa){
                //Disable
                LV_IMG_DECLARE(red_x_skills);
                lv_img_set_src(map_image, &red_x_skills);
                lv_btn_set_style(skills_button, LV_BTN_STYLE_REL, &location_button_style_rel); 
                raiseControllerWarning("Auton disabled");
                autonomousSelected = 6;
                sortingEnabled = 0;
            }else{
                //Regular
                color = 0;
                sortingEnabled = 1;
                lv_btn_set_style(skills_button, LV_BTN_STYLE_REL, &location_button_style_pr);
                raiseControllerWarning("Skills Auton");
                LV_IMG_DECLARE(field_skills);
                lv_img_set_src(map_image, &field_skills);
            }
            lv_btn_set_style(lr_button, LV_BTN_STYLE_REL, &location_button_style_rel);
            lv_btn_set_style(rb_button, LV_BTN_STYLE_REL, &location_button_style_rel);
            lv_btn_set_style(rr_button, LV_BTN_STYLE_REL, &location_button_style_rel);
            lv_btn_set_style(lb_button, LV_BTN_STYLE_REL, &location_button_style_rel);
            replay_button_style.body.main_color = LV_COLOR_BLACK;
            replay_button_style.body.grad_color = LV_COLOR_BLACK;
            lv_btn_set_style(replay_button, LV_BTN_STYLE_REL, &replay_button_style);
            //Change auton selector
            autonomousSelected = 4;
            break;
    }
    return LV_RES_OK;
}
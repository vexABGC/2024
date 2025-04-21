//Includes
#include "main.h" // IWYU pragma: keep
#include "autonPage.hpp"
#include "../src/globals.hpp"

//Static variable initialization
lv_obj_t* AutonPage::tabView = nullptr;
std::vector<void (*)()> AutonPage::callbacks = {};

//Constructor definition
AutonPage::AutonPage(const char* title, const char* description, void (*callback)()) {
    //Member variable initialization
    this->callback = callback;

    //Static variable addition
    callbacks.push_back(callback);

    //Create a new page
    page = lv_tabview_add_tab(tabView, title);
    
    //Add title to the page (Size 30 font)
    lv_obj_t* titleLabel = lv_label_create(page);
    lv_label_set_text(titleLabel, title);
    lv_obj_align(titleLabel, LV_ALIGN_TOP_MID, 0, 10);
    lv_obj_set_style_text_font(titleLabel, &lv_font_montserrat_30, LV_PART_MAIN);

    //Add description to the page
    lv_obj_t* descriptionLabel = lv_label_create(page);
    lv_label_set_text(descriptionLabel, description);
    lv_obj_align(descriptionLabel, LV_ALIGN_TOP_MID, 0, 50);
    lv_obj_set_style_text_font(descriptionLabel, &lv_font_montserrat_30, LV_PART_MAIN);
}

//Static Initialization function definition
void AutonPage::initialize() {
    //Tabview config
    tabView = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, 50);
}
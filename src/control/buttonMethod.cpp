//includes
#include "main.h"
#include "../src/control/buttonMethod.hpp"
#include "../src/globals.hpp"

//method definition
lv_res_t buttonMethod(lv_obj_t* btn){
	int id = lv_obj_get_free_num(btn);
    switch (id){
        case 0:
            //left select
            autonomousSelected = 0;
            lv_obj_clean(dSelect);
            lv_label_set_text(lv_label_create(dSelect, NULL), "left");
            break;
        case 1:
            //right select
            autonomousSelected = 1;
            lv_obj_clean(dSelect);
            lv_label_set_text(lv_label_create(dSelect, NULL), "right");
            break;
        case 2:
            //skills select
            autonomousSelected = 2;
            lv_obj_clean(dSelect);
            lv_label_set_text(lv_label_create(dSelect, NULL), "skills");
            break;
        case 3:
            //selector display (IGNORE)
            break;
    }
    return LV_RES_OK;
}
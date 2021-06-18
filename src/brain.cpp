#include "brain.hpp"

// https://github.com/lvgl/lv_demos/tree/v5.3/lv_tutorial
void autonSelectScreenInitialize(){
  lv_obj_t* autonScr = lv_page_create(NULL, NULL);
  lv_scr_load(autonScr);

  /*Create a button*/
  lv_obj_t* btn1 = lv_btn_create(autonScr, NULL);         /*Create a button on the currently loaded screen*/
  lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, btn_rel_action); /*Set function to be called when the button is released*/

  /*Create a label on the button (the 'label' variable can be reused)*/
  lv_obj_t* label = lv_label_create(btn1, NULL);
  lv_label_set_text(label, "Button 1");
}

static lv_res_t btn_rel_action(lv_obj_t* btn)
{
    /*Increase the button width*/
    lv_coord_t width = lv_obj_get_width(btn);
    lv_obj_set_width(btn, width + 20);

    return LV_RES_OK;
}

void brainPrint(std::string words){
  /*Create a Label on the currently active screen*/
lv_obj_t* label1 =  lv_label_create(lv_scr_act(), NULL);

/*Modify the Label's text*/
lv_label_set_text(label1, words.c_str());

/* Align the Label to the center
 * NULL means align on parent (which is the screen now)
 * 0, 0 at the end means an x, y offset after alignment*/
lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, 0);

}

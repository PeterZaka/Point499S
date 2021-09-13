#include "brain.hpp"
// https://github.com/lvgl/lv_demos/tree/v5.3/lv_tutorial
void autonSelectScreenInitialize(){
  init_button_styles();
  init_home_page();
  init_test_page();
  init_debug_page();
  init_auton_page();
  init_auton_make_page();
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

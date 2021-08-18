#include "pages.hpp"

void init_auton_page(){
  auton_page = lv_page_create(lv_scr_act(), NULL);
  lv_obj_set_size(auton_page, lv_obj_get_width(lv_scr_act()), lv_obj_get_height(lv_scr_act()));

  lv_obj_t* forwardBtn = createBtn(auton_page, 0, 0, 100, 100, "Forward", 1);
  lv_btn_set_action(forwardBtn, LV_BTN_ACTION_CLICK, btn_click_action);
}

void init_back_page(){
  back_page = lv_page_create(lv_scr_act(), NULL);
  hide(back_page);
  lv_obj_set_size(back_page, lv_obj_get_width(lv_scr_act()), lv_obj_get_height(lv_scr_act()));

  lv_obj_t* backBtn = createBtn(back_page, 0, 0, 100, 100, "Back", 0);
  lv_btn_set_action(backBtn, LV_BTN_ACTION_CLICK, btn_click_action);
}

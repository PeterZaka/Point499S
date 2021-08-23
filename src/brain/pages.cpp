#include "pages.hpp"

lv_obj_t* auton_page;
lv_obj_t* back_page;

lv_res_t btn_click_action(lv_obj_t* btn){
  uint8_t id = lv_obj_get_free_num(btn);
  switch (id){
    case 0:
      hide(back_page);
      show(auton_page);
      break;
    case 1:
      hide(auton_page);
      show(back_page);
      break;
  }
  return LV_RES_OK;
}

void init_auton_page(){
  auton_page = lv_page_create(lv_scr_act(), NULL);
  lv_obj_set_size(auton_page, lv_obj_get_width(lv_scr_act()), lv_obj_get_height(lv_scr_act()));

  lv_obj_t* forwardBtn = createBtn(auton_page, btn_style_mustang, 0, 0, 100, 100, "Forward", 1);
  lv_btn_set_action(forwardBtn, LV_BTN_ACTION_CLICK, btn_click_action);
}

void init_back_page(){
  back_page = lv_page_create(lv_scr_act(), NULL);
  hide(back_page);
  lv_obj_set_size(back_page, lv_obj_get_width(lv_scr_act()), lv_obj_get_height(lv_scr_act()));

  lv_obj_t* backBtn = createBtn(back_page, btn_style_mustang, 0, 0, 100, 100, "Back", 0);
  lv_btn_set_action(backBtn, LV_BTN_ACTION_CLICK, btn_click_action);

  lv_obj_t* midBtn = createBtn(back_page, btn_style_mustang, (450-250)/2, 0, 250, 100, "Mid", 3);
  lv_obj_t* toprightoffBtn = createBtn(back_page, btn_style_mustang, 450-100, 0, 100, 100, "Top Right\nthat is offset", 5);
}

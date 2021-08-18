#include "brain.hpp"

static const char* btnm_map[] = {"Test 1", "Test 2", "\n",
                                  "Test 3", "Test 4", ""};

static lv_res_t btn_click_action(lv_obj_t* btn){
  uint8_t id = lv_obj_get_free_num(btn);
  switch (id){
    case 0:
      hide(backPage);
      show(autonPage);
      break;
    case 1:
      hide(autonPage);
      show(backPage);
      break;
  }

  return LV_RES_OK;
}

// https://github.com/lvgl/lv_demos/tree/v5.3/lv_tutorial
void autonSelectScreenInitialize(){
  autonPage = lv_page_create(lv_scr_act(), NULL);
  lv_obj_set_size(autonPage, lv_obj_get_width(lv_scr_act()), lv_obj_get_height(lv_scr_act()));

  lv_obj_t* forwardBtn = createBtn(autonPage, 0, 0, 100, 100, "Forward", 1);
  lv_btn_set_action(forwardBtn, LV_BTN_ACTION_CLICK, btn_click_action);

  backPage = lv_page_create(lv_scr_act(), NULL);
  hide(backPage);
  lv_obj_set_size(backPage, lv_obj_get_width(lv_scr_act()), lv_obj_get_height(lv_scr_act()));

  lv_obj_t* backBtn = createBtn(backPage, 0, 0, 100, 100, "Back", 0);
  lv_btn_set_action(backBtn, LV_BTN_ACTION_CLICK, btn_click_action);
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

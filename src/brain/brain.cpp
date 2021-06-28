#include "brain.hpp"

static lv_obj_t* autonPage;
static lv_obj_t* backPage;

static const char* btnm_map[] = {"Test 1", "Test 2", "\n",
                                  "Test 3", "Test 4", ""};

static lv_res_t event_handler(lv_obj_t* obj, const char* txt){
  hide(autonPage);
  show(backPage);
  printf("%s was pressed\n", txt);
  return LV_RES_OK;
}

static lv_res_t btn_click_action(lv_obj_t* btn){
  uint8_t id = lv_obj_get_free_num(btn);
  if(id == 0){
    hide(backPage);
    show(autonPage);
  }

  return LV_RES_OK;
}

// https://github.com/lvgl/lv_demos/tree/v5.3/lv_tutorial
void autonSelectScreenInitialize(){
  autonPage = lv_page_create(lv_scr_act(), NULL);
  lv_obj_set_size(autonPage, lv_obj_get_width(lv_scr_act()), lv_obj_get_height(lv_scr_act()));
  lv_obj_align(autonPage, NULL, LV_ALIGN_CENTER, 0, 0);

  lv_obj_t* btnm1 = lv_btnm_create(autonPage, NULL);
  lv_btnm_set_map(btnm1, btnm_map);
  lv_obj_set_size(autonPage, lv_obj_get_width(lv_scr_act()), lv_obj_get_height(lv_scr_act()));
  lv_obj_align(btnm1, NULL, LV_ALIGN_CENTER, 0, 0);
  lv_btnm_set_action(btnm1, event_handler);

  backPage = lv_page_create(autonPage, NULL);
  hide(backPage);
  lv_obj_set_size(backPage, lv_obj_get_width(lv_scr_act()), lv_obj_get_height(lv_scr_act()));
  lv_obj_align(backPage, NULL, LV_ALIGN_CENTER, 0, 0);

  lv_obj_t* backBtn = createBtn(backPage, 0, 0, 50, 50, "Back", 0);
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

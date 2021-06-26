#include "brain.hpp"

static lv_obj_t* autonContainer;
static lv_obj_t* countdownContainer;
static lv_obj_t* countdownLabel;

static const char * btnm_map[] = {"Test 1", "Test 2", "\n",
                                  "Test 3", "Test 4", ""};

static void countdown(){
  lv_obj_set_hidden(countdownContainer, false);
  lv_label_set_text(countdownLabel, "3");
  pros::delay(1000);
  lv_label_set_text(countdownLabel, "2");
  pros::delay(1000);
  lv_label_set_text(countdownLabel, "1");
  pros::delay(1000);
  lv_label_set_text(countdownLabel, "");
  lv_obj_set_hidden(countdownContainer, true);
}

static lv_res_t event_handler(lv_obj_t* obj, const char* txt){
  lv_obj_set_hidden(autonContainer, true);
  printf("%s was pressed\n", txt);
  countdown();
  lv_obj_set_hidden(autonContainer, false);
  return LV_RES_OK;
}

// https://github.com/lvgl/lv_demos/tree/v5.3/lv_tutorial
void autonSelectScreenInitialize(){
  autonContainer = lv_obj_create(lv_scr_act(), NULL);
  lv_obj_set_size(autonContainer, lv_obj_get_width(lv_scr_act()), lv_obj_get_height(lv_scr_act()));
  lv_obj_align(autonContainer, NULL, LV_ALIGN_CENTER, 0, 0);

  lv_obj_t* btnm1 = lv_btnm_create(autonContainer, NULL);
  lv_btnm_set_map(btnm1, btnm_map);
  lv_obj_align(btnm1, NULL, LV_ALIGN_CENTER, 0, 0);
  lv_btnm_set_action(btnm1, event_handler);

  countdownContainer = lv_obj_create(lv_scr_act(), NULL);
  lv_obj_set_size(countdownContainer, lv_obj_get_width(lv_scr_act()), lv_obj_get_height(lv_scr_act()));
  lv_obj_align(countdownContainer, NULL, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_hidden(countdownContainer, true);
  countdownLabel =  lv_label_create(countdownContainer, NULL);
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

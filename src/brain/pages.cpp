#include "pages.hpp"

lv_obj_t* auton_page;
lv_obj_t* test_page;

testSelection Test = none;

static void countdown(){
  lv_obj_t* countdown_label =  lv_label_create(lv_scr_act(), NULL);
  lv_obj_align(countdown_label, NULL, LV_ALIGN_CENTER, 0, 0);
  lv_label_set_text(countdown_label, "3");
  pros::delay(1000);
  lv_label_set_text(countdown_label, "2");
  pros::delay(1000);
  lv_label_set_text(countdown_label, "1");
  pros::delay(1000);
  lv_obj_del(countdown_label);
}

lv_res_t btn_click_action(lv_obj_t* btn){
  uint8_t id = lv_obj_get_free_num(btn);
  std::cout << "Pressed: " << (int)id << std::endl;
  if (id == 0) {
    hide(test_page);
    show(auton_page);
  } else if (id == 1) {
    hide(auton_page);
    show(test_page);
  } else if (id == 2) {
    pros::Task countdown_task(countdown);
    Test = drive;
  } else if (id == 3) {
    pros::Task countdown_task(countdown);
    Test = turn;
  } else if (id == 4) {
    pros::Task countdown_task(countdown);
    Test = diagonal;
  } else if (id == 5) {
    pros::Task countdown_task(countdown);
    Test = curve;
  }
  return LV_RES_OK;
}

void init_auton_page(){
  auton_page = lv_page_create(lv_scr_act(), NULL);
  lv_obj_set_size(auton_page, lv_obj_get_width(lv_scr_act()), lv_obj_get_height(lv_scr_act()));

  lv_obj_t* forwardBtn = createBtn(auton_page, btn_style_mustang, 0, 0, 100, 100, "Forward", 1);
  lv_btn_set_action(forwardBtn, LV_BTN_ACTION_CLICK, btn_click_action);
}

// width: 450
// height: 210

void init_test_page(){
  test_page = lv_page_create(lv_scr_act(), NULL);
  hide(test_page);
  lv_obj_set_size(test_page, lv_obj_get_width(lv_scr_act()), lv_obj_get_height(lv_scr_act()));

  lv_obj_t* homeBtn = createBtn(test_page, btn_style_mustang, 0, 0, 50, 50, "Home", 0);
  lv_btn_set_action(homeBtn, LV_BTN_ACTION_CLICK, btn_click_action);

  lv_obj_t* driveTestBtn = createBtn(test_page, btn_style_mustang, 60, 0, 190, 100, "Drive Test", 2);
  lv_btn_set_action(driveTestBtn, LV_BTN_ACTION_CLICK, btn_click_action);

  lv_obj_t* turnTestBtn = createBtn(test_page, btn_style_mustang, 260, 0, 190, 100, "Turn Test", 3);
  lv_btn_set_action(turnTestBtn, LV_BTN_ACTION_CLICK, btn_click_action);

  lv_obj_t* diagonalTestBtn = createBtn(test_page, btn_style_mustang, 60, 110, 190, 100, "Diagonal Test", 4);
  lv_btn_set_action(diagonalTestBtn, LV_BTN_ACTION_CLICK, btn_click_action);

  lv_obj_t* curveTestBtn = createBtn(test_page, btn_style_mustang, 260, 110, 190, 100, "Curve Test", 5);
  lv_btn_set_action(curveTestBtn, LV_BTN_ACTION_CLICK, btn_click_action);

  //lv_obj_t* midBtn = createBtn(back_page, btn_style_red, (450-250)/2, 0, 250, 210, "Mid", 2);
}

#include "pages.hpp"

lv_obj_t* home_page;
lv_obj_t* test_page;
lv_obj_t* debug_page;
lv_obj_t* auton_page;
lv_obj_t* auton_make_page;

testSelection Test = none;
bool isDebugging = false;

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
    Test = none;
    isDebugging = false;
    hide(test_page);
    hide(debug_page);
    hide(auton_page);
    hide(auton_make_page);
    show(home_page);
  } else if (id == 1) {
    hide(home_page);
    hide(debug_page);
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
  } else if (id == 6) {
    isDebugging = true;
    hide(home_page);
    hide(test_page);
    show(debug_page);
  } else if (id == 7) {
    xPos = 0;
    yPos = 0;
    iSensor.tare();
  } else if (id == 8) {
    hide(home_page);
    hide(test_page);
    hide(debug_page);
    hide(auton_make_page);
    show(auton_page);
  }
  return LV_RES_OK;
}

void init_home_page(){
  home_page = lv_page_create(lv_scr_act(), NULL);
  lv_obj_set_size(home_page, lv_obj_get_width(lv_scr_act()), lv_obj_get_height(lv_scr_act()));
  hide(home_page);
  //
  // lv_obj_t* testBtn = createBtn(home_page, btn_style_mustang, 0, 0, 100, 100, "Test", 1);
  // lv_btn_set_action(testBtn, LV_BTN_ACTION_CLICK, btn_click_action);
  //
  // lv_obj_t* debugBtn = createBtn(home_page, btn_style_mustang, 110, 0, 100, 100, "Debug", 6);
  // lv_btn_set_action(debugBtn, LV_BTN_ACTION_CLICK, btn_click_action);
  //
  // lv_obj_t* autonBtn = createBtn(home_page, btn_style_mustang, 220, 0, 100, 100, "Auton", 8);
  // lv_btn_set_action(autonBtn, LV_BTN_ACTION_CLICK, btn_click_action);

  Page* HomePage = new Page();
  Page* AutonPage = new Page();

  // Home Page
  Button autonBtn(HomePage, 0, 100, 100, 100, "Auton");
  autonBtn.setFunction(AutonPage->show);

  // Auton Page
  Button homeBtn(AutonPage, 0, 0, 100, 100, "Home");

  homeBtn.setFunction(HomePage->show);
  autonLabel = lv_label_create(AutonPage->lv_page, NULL);
  lv_obj_align(autonLabel, NULL, LV_ALIGN_CENTER, 0, 150);

  changeToLeftAuton();
  Button leftBtn(AutonPage, 100, 0, 150, 100, "Left Auton");
  leftBtn.setFunction(changeToLeftAuton);
  Button rightBtn(AutonPage, 250, 0, 150, 100, "Right Auton");
  rightBtn.setFunction(changeToRightAuton);
  Button skillsBtn(AutonPage, 100, 100, 150, 100, "Skills");
  skillsBtn.setFunction(changeToSkills);

  HomePage->show();
}

// width: 450
// height: 210

void init_test_page(){
  test_page = lv_page_create(lv_scr_act(), NULL);
  hide(test_page);
  lv_obj_set_size(test_page, lv_obj_get_width(lv_scr_act()), lv_obj_get_height(lv_scr_act()));

  lv_obj_t* homeBtn = createBtn(test_page, btn_style_mustang, 0, 0, 50, 50, "Home", 0);
  lv_btn_set_action(homeBtn, LV_BTN_ACTION_CLICK, btn_click_action);
  lv_obj_t* debugBtn = createBtn(test_page, btn_style_mustang, 0, 55, 50, 50, "Debug", 6);
  lv_btn_set_action(debugBtn, LV_BTN_ACTION_CLICK, btn_click_action);

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

static lv_obj_t* xPos_label;
static lv_obj_t* yPos_label;
static lv_obj_t* rot_label;

void init_debug_page(){
  debug_page = lv_page_create(lv_scr_act(), NULL);
  hide(debug_page);
  lv_obj_set_size(debug_page, lv_obj_get_width(lv_scr_act()), lv_obj_get_height(lv_scr_act()));

  lv_obj_t* homeBtn = createBtn(debug_page, btn_style_mustang, 0, 0, 50, 50, "Home", 0);
  lv_btn_set_action(homeBtn, LV_BTN_ACTION_CLICK, btn_click_action);

  lv_obj_t* resetBtn = createBtn(debug_page, btn_style_mustang, 0, 55, 50, 50, "Reset", 7);
  lv_btn_set_action(resetBtn, LV_BTN_ACTION_CLICK, btn_click_action);

  xPos_label =  lv_label_create(debug_page, NULL);
  yPos_label =  lv_label_create(debug_page, NULL);
  rot_label =  lv_label_create(debug_page, NULL);

  lv_obj_align(xPos_label, NULL, LV_ALIGN_IN_LEFT_MID, 60, 0);
  lv_obj_align(yPos_label, NULL, LV_ALIGN_IN_LEFT_MID, 60, 25);
  lv_obj_align(rot_label, NULL, LV_ALIGN_IN_LEFT_MID, 60, 50);
}

void update_debug_page(){
  std::string text = "x: " + std::to_string(xPos);
  lv_label_set_text(xPos_label, text.c_str());
  text = "y: " + std::to_string(yPos);
  lv_label_set_text(yPos_label, text.c_str());
  text = "rot: " + std::to_string(rot);
  lv_label_set_text(rot_label, text.c_str());
}

void init_auton_page(){
  auton_page = lv_page_create(lv_scr_act(), NULL);
  hide(auton_page);
  lv_obj_set_size(auton_page, lv_obj_get_width(lv_scr_act()), lv_obj_get_height(lv_scr_act()));

  lv_obj_t* homeBtn = createBtn(auton_page, btn_style_mustang, 0, 0, 50, 50, "Home", 0);
  lv_btn_set_action(homeBtn, LV_BTN_ACTION_CLICK, btn_click_action);
}

void init_auton_make_page(){
  auton_make_page = lv_page_create(lv_scr_act(), NULL);
  hide(auton_make_page);
  lv_obj_set_size(auton_make_page, lv_obj_get_width(lv_scr_act()), lv_obj_get_height(lv_scr_act()));

  lv_obj_t* homeBtn = createBtn(auton_make_page, btn_style_mustang, 0, 0, 50, 50, "Home", 0);
  lv_btn_set_action(homeBtn, LV_BTN_ACTION_CLICK, btn_click_action);
}

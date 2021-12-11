#include "brain/autonPage.hpp"

static const double SCREENWIDTH = 450;
static const double SCREENHEIGHT = 210;

std::map<std::string, std::function<void()>> autonSelectionMap;
std::function<void()> autonFunc;
lv_obj_t* autonLabel;

void initalize_auton_page(lv_obj_t* autonPage){
  autonLabel = lv_label_create(autonPage, NULL);
  lv_obj_align(autonLabel, NULL, LV_ALIGN_CENTER, SCREENWIDTH / 2.0, SCREENHEIGHT - 50);

  autonSelectionMap["Left Auton"] = leftAuton;
  autonSelectionMap["Right Auton"] = rightAuton;
  autonSelectionMap["Skills"] = skills;
  autonSelectionMap["Test"] = testAuton;
}

std::function<void()> changeAutonFunc(std::string auton){
  return [&]{
    lv_label_set_text(autonLabel, auton.c_str());
    autonFunc = autonSelectionMap[auton];
  };
}

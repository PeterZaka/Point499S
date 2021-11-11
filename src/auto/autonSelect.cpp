#include "brain/autonSelect.hpp"

std::function<void()> autonFunc;
lv_obj_t* autonLabel;

void changeToLeftAuton(){
  lv_label_set_text(autonLabel, "Left Auton");
  autonFunc = leftAuton;
}

void changeToRightAuton(){
  lv_label_set_text(autonLabel, "Right Auton");
  autonFunc = rightAuton;
}

void changeToSkills(){
  lv_label_set_text(autonLabel, "Skills");
  autonFunc = skills;
}

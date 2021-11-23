#include "brain.hpp"

void autonSelectScreenInitialize(){
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

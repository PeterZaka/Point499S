#include "brain.hpp"

void autonSelectScreenInitialize(){
  Page* HomePage = new Page();
  Page* AutonPage = new Page();
  Page* TemperaturePage = new Page();

  // ------- Home Page -------
  Button autonBtn(HomePage, 0, 100, 100, 100, "Auton");
  autonBtn.setFunction(AutonPage->show);
  Button temperatureBtn(HomePage, 100, 100, 100, 100, "Temperature");
  temperatureBtn.setFunctions({TemperaturePage->show, startTemperatureUpdateTask});
  temperatureUpdateTask.suspend();


  // ------- Auton Page -------
  Button autonToHomeBtn(AutonPage, 0, 0, 100, 100, "Home");
  autonToHomeBtn.setFunction(HomePage->show);

  autonLabel = lv_label_create(AutonPage->lv_page, NULL);
  lv_obj_align(autonLabel, NULL, LV_ALIGN_CENTER, 0, 150);

  changeToLeftAuton();
  Button leftBtn(AutonPage, 100, 0, 150, 100, "Left Auton");
  leftBtn.setFunction(changeToLeftAuton);
  Button rightBtn(AutonPage, 250, 0, 150, 100, "Right Auton");
  rightBtn.setFunction(changeToRightAuton);
  Button skillsBtn(AutonPage, 100, 100, 150, 100, "Skills");
  skillsBtn.setFunction(changeToSkills);


  // ------- Temperature Page -------
  Button temperatureToHomeBtn(TemperaturePage, 0, 0, 100, 100, "Home");
  temperatureToHomeBtn.setFunctions({HomePage->show, endTemperatureUpdateTask});

  initalize_temperature_labels(TemperaturePage->lv_page);


  HomePage->show();
}

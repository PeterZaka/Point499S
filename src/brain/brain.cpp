#include "brain.hpp"

void autonSelectScreenInitialize(){
  Page* HomePage = new Page();
  Page* AutonPage = new Page();
  Page* TemperaturePage = new Page();
  Page* VisionPage = new Page();
  Page* OdometryPage = new Page();

  // ------- Home Page -------
  Button autonBtn(HomePage, 0, 100, 100, 100, "Auton");
  autonBtn.setFunction(AutonPage->show);

  Button temperatureBtn(HomePage, 100, 0, 100, 100, "Temperature");
  temperatureBtn.setFunctions({startTemperatureUpdateTask, TemperaturePage->show});

  Button visionBtn(HomePage, 200, 0, 100, 100, "Vision");
  visionBtn.setFunctions({VisionPage->show, startVisionUpdateTask});

  Button odometryBtn(HomePage, 300, 0, 100, 100, "Odometry");
  odometryBtn.setFunctions({OdometryPage->show, startOdometryUpdateTask});


  // ------- Auton Page -------
  Button autonToHomeBtn(AutonPage, 0, 0, 100, 100, "Home");
  autonToHomeBtn.setFunction(HomePage->show);

  initalize_auton_page(AutonPage->lv_page);

  changeAutonFunc("Test")();
  Button leftBtn(AutonPage, 100, 0, 150, 80, "Left Auton");
  leftBtn.setFunction(changeAutonFunc("Left Auton"));
  Button rightBtn(AutonPage, 250, 0, 150, 80, "Right Auton");
  rightBtn.setFunction(changeAutonFunc("Right Auton"));
  Button skillsBtn(AutonPage, 100, 80, 150, 80, "Skills");
  skillsBtn.setFunction(changeAutonFunc("Skills"));
  Button testBtn(AutonPage, 250, 80, 150, 80, "Test");
  testBtn.setFunction(changeAutonFunc("Test"));


  // ------- Temperature Page -------
  Button temperatureToHomeBtn(TemperaturePage, 0, 0, 100, 100, "Home");
  temperatureToHomeBtn.setFunctions({HomePage->show, endTemperatureUpdateTask});

  initalize_temperature_page(TemperaturePage->lv_page);


  // ------- Vision Page -------
  Button visionToHomeBtn(VisionPage, 0, 0, 100, 100, "Home");
  visionToHomeBtn.setFunctions({HomePage->show, endVisionUpdateTask});

  initalize_vision_page(VisionPage->lv_page);


  // ------- Odometry Page -------
  Button odometryToHomeBtn(OdometryPage, 0, 0, 100, 100, "Home");
  odometryToHomeBtn.setFunctions({HomePage->show, endOdometryUpdateTask});

  initalize_odometry_page(OdometryPage->lv_page);


  isAllInit = true;
  HomePage->show();
}

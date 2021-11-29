#include "brain/temperaturePage.hpp"

lv_obj_t* leftLiftTempLabel;
lv_obj_t* rightLiftTempLabel;
// lv_obj_t* frontClawTempLabel;
lv_obj_t* backClawTempLabel;
lv_obj_t* topLeftMotorTempLabel;
lv_obj_t* topRightTempLabel;
lv_obj_t* backLeftTempLabel;
lv_obj_t* backRightTempLabel;

static std::string temperatureString(std::string words, double celsius){
  return (words + std::to_string((int)((9.0/5.0) * celsius + 32)));
}

static void updateTemperature(){
  if (!isAllInit) return;

  lv_label_set_text(leftLiftTempLabel, temperatureString("Left Lift: ", leftLift.getTemperature()).c_str());
  lv_label_set_text(rightLiftTempLabel, temperatureString("Right Lift: ", rightLift.getTemperature()).c_str());
  // lv_label_set_text(frontClawTempLabel, temperatureString("Front Claw: ", clawFront.getTemperature()).c_str());
  lv_label_set_text(backClawTempLabel, temperatureString("Back Claw: ", clawBack.getTemperature()).c_str());
  lv_label_set_text(topLeftMotorTempLabel, temperatureString("TL Wheel: ", topLeftMotor.getTemperature()).c_str());
  lv_label_set_text(topRightTempLabel, temperatureString("TR Wheel: ", topRightMotor.getTemperature()).c_str());
  lv_label_set_text(backLeftTempLabel, temperatureString("BL Wheel: ", backLeftMotor.getTemperature()).c_str());
  lv_label_set_text(backRightTempLabel, temperatureString("BR Wheel: ", backRightMotor.getTemperature()).c_str());
  // temperatureString("BR Wheel: ", backRightMotor.getTemperature())
}

pros::Task temperatureUpdateTask([]{
  while (true) {
    updateTemperature();
    pros::delay(1000);
  }
});

void initalize_temperature_page(lv_obj_t* temperaturePage){
  temperatureUpdateTask.suspend();

  leftLiftTempLabel = lv_label_create(temperaturePage, NULL);
  rightLiftTempLabel = lv_label_create(temperaturePage, NULL);
  // frontClawTempLabel = lv_label_create(temperaturePage, NULL);
  backClawTempLabel = lv_label_create(temperaturePage, NULL);
  topLeftMotorTempLabel = lv_label_create(temperaturePage, NULL);
  topRightTempLabel = lv_label_create(temperaturePage, NULL);
  backLeftTempLabel = lv_label_create(temperaturePage, NULL);
  backRightTempLabel = lv_label_create(temperaturePage, NULL);
  lv_obj_align(leftLiftTempLabel, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 100);
  lv_obj_align(rightLiftTempLabel, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 125);
  // lv_obj_align(frontClawTempLabel, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 150);
  lv_obj_align(backClawTempLabel, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 175);
  lv_obj_align(topLeftMotorTempLabel, NULL, LV_ALIGN_IN_TOP_LEFT, 200, 100);
  lv_obj_align(topRightTempLabel, NULL, LV_ALIGN_IN_TOP_LEFT, 200, 125);
  lv_obj_align(backLeftTempLabel, NULL, LV_ALIGN_IN_TOP_LEFT, 200, 150);
  lv_obj_align(backRightTempLabel, NULL, LV_ALIGN_IN_TOP_LEFT, 200, 175);
}

void startTemperatureUpdateTask(){
  temperatureUpdateTask.resume();
}

void endTemperatureUpdateTask(){
  temperatureUpdateTask.suspend();
}

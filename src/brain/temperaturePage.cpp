#include "brain/temperaturePage.hpp"

lv_obj_t* leftLiftTempLabel;
lv_obj_t* rightLiftTempLabel;
lv_obj_t* frontClawTempLabel;
lv_obj_t* backClawTempLabel;
lv_obj_t* topLeftMotorTempLabel;
lv_obj_t* topRightTempLabel;
lv_obj_t* backLeftTempLabel;
lv_obj_t* backRightTempLabel;

static const char* temperatureString(std::string words, double celsius){
  return (words + std::to_string((int)((9.0/5.0) * celsius + 32))).c_str();
}

static void updateTemperature(){
  lv_label_set_text(leftLiftTempLabel, temperatureString("Left Lift: ", leftLift.getTemperature()));
  lv_label_set_text(leftLiftTempLabel, temperatureString("Right Lift: ", rightLift.getTemperature()));
  lv_label_set_text(leftLiftTempLabel, temperatureString("Front Claw: ", clawFront.getTemperature()));
  lv_label_set_text(leftLiftTempLabel, temperatureString("Back Claw: ", clawBack.getTemperature()));
  lv_label_set_text(leftLiftTempLabel, temperatureString("TL Wheel: ", topLeftMotor.getTemperature()));
  lv_label_set_text(leftLiftTempLabel, temperatureString("TR Wheel: ", topRightMotor.getTemperature()));
  lv_label_set_text(leftLiftTempLabel, temperatureString("BL Wheel: ", backLeftMotor.getTemperature()));
  lv_label_set_text(leftLiftTempLabel, temperatureString("BR Wheel: ", backRightMotor.getTemperature()));
}

pros::Task temperatureUpdateTask([]{
  updateTemperature();
  pros::delay(1000);
});

void initalize_temperature(lv_obj_t* temperaturePage){
  temperatureUpdateTask.suspend();

  leftLiftTempLabel = lv_label_create(temperaturePage, NULL);
  rightLiftTempLabel = lv_label_create(temperaturePage, NULL);
  frontClawTempLabel = lv_label_create(temperaturePage, NULL);
  backClawTempLabel = lv_label_create(temperaturePage, NULL);
  topLeftMotorTempLabel = lv_label_create(temperaturePage, NULL);
  topRightTempLabel = lv_label_create(temperaturePage, NULL);
  backLeftTempLabel = lv_label_create(temperaturePage, NULL);
  backRightTempLabel = lv_label_create(temperaturePage, NULL);
  lv_obj_align(leftLiftTempLabel, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 100);
  lv_obj_align(rightLiftTempLabel, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 125);
  lv_obj_align(frontClawTempLabel, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 150);
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

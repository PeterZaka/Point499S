#pragma once

#include "pros/apix.h"
#include "brainClasses/Button.hpp"
#include "robot-config.hpp"

extern pros::Task temperatureUpdateTask;
extern lv_obj_t* leftLiftTempLabel;
extern lv_obj_t* rightLiftTempLabel;
extern lv_obj_t* frontClawTempLabel;
extern lv_obj_t* backClawTempLabel;
extern lv_obj_t* topLeftMotorTempLabel;
extern lv_obj_t* topRightTempLabel;
extern lv_obj_t* backLeftTempLabel;
extern lv_obj_t* backRightTempLabel;

void initalize_temperature_page(lv_obj_t* temperaturePage);

void startTemperatureUpdateTask();

void endTemperatureUpdateTask();

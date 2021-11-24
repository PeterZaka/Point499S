#pragma once

#include "pros/apix.h"
#include "brainClasses/Button.hpp"
#include "brainClasses/Style.hpp"
#include "robot-config.hpp"

extern pros::Task visionUpdateTask;

void initalize_vision(lv_obj_t* visionPage);

void startVisionUpdateTask();

void endVisionUpdateTask();

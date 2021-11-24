#pragma once

#include "pros/apix.h"
#include "brainClasses/Button.hpp"
#include "brainClasses/Style.hpp"
#include "auto/odometry.hpp"

extern pros::Task odometryUpdateTask;

void initalize_odometry_page(lv_obj_t* odometryPage);

void startOdometryUpdateTask();

void endOdometryUpdateTask();

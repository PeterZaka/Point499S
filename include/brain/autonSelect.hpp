#pragma once

#include "pros/apix.h"
#include "auto/autonomous.hpp"
#include <functional>

extern std::function<void()> autonFunc;
extern lv_obj_t* autonLabel;

void changeToLeftAuton();

void changeToRightAuton();

void changeToLeftNewAuton();

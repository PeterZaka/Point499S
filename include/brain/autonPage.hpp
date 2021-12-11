#pragma once

#include "pros/apix.h"
#include "auto/autonomous.hpp"
#include <functional>
#include <map>

extern std::map<std::string, std::function<void()>> autonSelectionMap;
extern std::function<void()> autonFunc;
extern lv_obj_t* autonLabel;

void initalize_auton_page(lv_obj_t* autonPage);

std::function<void()> changeAutonFunc(std::string auton);

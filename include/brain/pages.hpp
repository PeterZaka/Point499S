#pragma once

#include <functional>
#include "pros/apix.h"
#include "brain/lvglHelper.hpp"
#include "brain/config.hpp"
#include "auto/autonomous.hpp"

extern lv_obj_t* auton_page;
extern lv_obj_t* test_page;

lv_res_t btn_click_action(lv_obj_t* btn);

void init_auton_page();

void init_test_page();

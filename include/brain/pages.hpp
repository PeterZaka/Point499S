#pragma once

#include "pros/apix.h"
#include "brain/lvglHelper.hpp"

extern lv_obj_t* auton_page;
extern lv_obj_t* back_page;

lv_res_t btn_click_action(lv_obj_t* btn);

void init_auton_page();

void init_back_page();

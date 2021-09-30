#pragma once

#include "brainClasses/Page.hpp"
#include "brainClasses/Button.hpp"
#include "pros/apix.h"
#include "brain/lvglHelper.hpp"
#include "brain/config.hpp"
#include "auto/autonomous.hpp"
#include "auto/odometry.hpp"

extern lv_obj_t* home_page;
extern lv_obj_t* test_page;
extern lv_obj_t* debug_page;
extern lv_obj_t* auton_page;
extern lv_obj_t* auton_make_page;

enum testSelection{
  none,
  drive,
  turn,
  diagonal,
  curve
};

extern testSelection Test;
extern bool isDebugging;

lv_res_t btn_click_action(lv_obj_t* btn);

void init_home_page();

void init_test_page();

void init_debug_page();

void update_debug_page();

void init_auton_page();

void init_auton_make_page();

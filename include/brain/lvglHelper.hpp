#pragma once

#include "pros/apix.h"

lv_obj_t* createBtn(lv_obj_t* parent, lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height,
    const char* text, int id);

void show(lv_obj_t* page);
void hide(lv_obj_t* page);

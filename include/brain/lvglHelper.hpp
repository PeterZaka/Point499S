#pragma once

#include "pros/apix.h"

enum btn_style_499 {
  btn_style_mustang,
  btn_style_blue,
  btn_style_red
};

lv_style_t make_style(lv_color_t main_color, lv_color_t border_color, lv_color_t text_color,
                      int radius, int border_width);

void init_button_styles();

lv_obj_t* createBtn(lv_obj_t* parent, btn_style_499 Btn_style,
    lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height,
    const char* text, int id=-1);

void show(lv_obj_t* page);
void hide(lv_obj_t* page);

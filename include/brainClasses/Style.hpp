#pragma once

#include "pros/apix.h"

class Style {

public:
  Style() = default;

  void setReleased(lv_color_t main_color, lv_color_t border_color, lv_color_t text_color,
                      int radius, int border_width);

  void setPressed(lv_color_t main_color, lv_color_t border_color, lv_color_t text_color,
                      int radius, int border_width);

  void setBoth(lv_color_t main_color, lv_color_t border_color, lv_color_t text_color,
                      int radius, int border_width);

  lv_style_t released;
  lv_style_t pressed;

  static lv_style_t make_style(lv_color_t main_color, lv_color_t border_color, lv_color_t text_color,
                      int radius, int border_width);
};

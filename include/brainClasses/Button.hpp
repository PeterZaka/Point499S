#pragma once

#include "pros/apix.h"
#include <map>
#include <functional>

class Button {

public:

  Button(lv_obj_t* parent, lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height,
         std::string text);

  void setFunction(std::function<void()> func);

  static int next_id;
  static std::unordered_map<int, std::function<void()>> id_function;

private:
  lv_obj_t* lv_btn;
  lv_obj_t* label;

};

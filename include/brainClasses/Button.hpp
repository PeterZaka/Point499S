#pragma once

#include "pros/apix.h"
#include "brainClasses/Page.hpp"
#include "brainClasses/Style.hpp"
#include <map>
#include <functional>

class Button {

public:

  Button(Page* page , lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height,
         std::string text);

  void setFunction(std::function<void()> func);
  
  void setStyle(Style style);

  static int next_id;
  static std::unordered_map<int, std::function<void()>> id_function;

private:
  lv_obj_t* lv_btn;
  lv_obj_t* label;

};

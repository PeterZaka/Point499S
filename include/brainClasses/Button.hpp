#pragma once

#include "pros/apix.h"
#include "brainClasses/Page.hpp"
#include "brainClasses/Style.hpp"
#include <vector>
#include <map>
#include <functional>

extern bool isAllInit;

class Button {

public:

  Button(lv_obj_t* lv_page, lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height,
         std::string text);

  Button(Page* page , lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height,
         std::string text);

  void setFunction(std::function<void()> func);

  void setFunctions(std::vector<std::function<void()>> funcs);

  void setStyle(Style& style);

  lv_obj_t* lv_btn;
  lv_obj_t* label;

  static int next_id;
  static std::unordered_map<int, std::vector<std::function<void()>>> id_function;

};

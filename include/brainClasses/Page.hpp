#pragma once

#include "pros/apix.h"
#include <vector>
#include <functional>

class Page {

public:

  Page();

  void showPage();
  std::function<void()> show;

  lv_obj_t* lv_page;
  static std::vector<lv_obj_t*> allPages;

private:

};

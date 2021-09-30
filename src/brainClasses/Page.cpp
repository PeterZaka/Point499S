#include "brainClasses/Page.hpp"

std::vector<lv_obj_t*> Page::allPages;

Page::Page(){
  lv_page = lv_page_create(lv_scr_act(), NULL);
  lv_obj_set_size(lv_page, lv_obj_get_width(lv_scr_act()), lv_obj_get_height(lv_scr_act()));
  Page::allPages.push_back(lv_page);
  std::function<void()> show = [this](){showPage();};
}

void Page::showPage(){
  for (auto p: Page::allPages) lv_obj_set_hidden(p, true);
  lv_obj_set_hidden(lv_page, false);
}

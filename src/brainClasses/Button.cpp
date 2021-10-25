#include "brainClasses/Button.hpp"

int Button::next_id = 0;
std::unordered_map<int, std::function<void()>> Button::id_function;

static lv_res_t click_function(lv_obj_t* btn){
  Button::id_function[lv_obj_get_free_num(btn)]();
  return LV_RES_OK;
}

Button::Button(Page* page, lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height,
       std::string text){
   lv_btn = lv_btn_create(page->lv_page, NULL);
   lv_obj_set_pos(lv_btn, x, y);
   lv_obj_set_size(lv_btn, width, height);
   lv_obj_set_free_num(lv_btn, Button::next_id++);

   label = lv_label_create(lv_btn, NULL);
   lv_label_set_text(label, text.c_str());
   lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);
   lv_btn_set_action(lv_btn, LV_BTN_ACTION_CLICK, click_function);
}

void Button::setFunction(std::function<void()> func){
  Button::id_function[lv_obj_get_free_num(lv_btn)] = func;
}

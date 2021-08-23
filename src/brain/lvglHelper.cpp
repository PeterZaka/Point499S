#include "brain/lvglHelper.hpp"

static lv_style_t btn_style_mustang_rel;
static lv_style_t btn_style_mustang_pr;

static const lv_color_t MUSTANG_RED = LV_COLOR_MAKE(204, 32, 39);
static const lv_color_t MUSTANG_CHARCOAL = LV_COLOR_MAKE(65, 64, 66);
static const lv_color_t MUSTANG_LITE_GRAY = LV_COLOR_MAKE(184, 194, 192);

void init_button_styles(){
  lv_style_copy(&btn_style_mustang_rel, &lv_style_plain);
  btn_style_mustang_rel.body.radius = 10;
  btn_style_mustang_rel.body.border.width = 10;
  btn_style_mustang_rel.body.main_color = MUSTANG_RED;
  btn_style_mustang_rel.body.grad_color = MUSTANG_RED;
  btn_style_mustang_rel.body.border.color = MUSTANG_CHARCOAL;
  btn_style_mustang_rel.text.color = MUSTANG_LITE_GRAY;

  lv_style_copy(&btn_style_mustang_pr, &lv_style_plain);
  btn_style_mustang_pr.body.radius = 10;
  btn_style_mustang_pr.body.border.width = 10;
  btn_style_mustang_pr.body.main_color = MUSTANG_RED;
  btn_style_mustang_pr.body.grad_color = MUSTANG_RED;
  btn_style_mustang_pr.body.border.color = MUSTANG_LITE_GRAY;
  btn_style_mustang_pr.text.color = MUSTANG_CHARCOAL;
}

lv_obj_t* createBtn(lv_obj_t* parent, btn_style_499 Btn_style,
    lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height,
    const char* text, int id) {
    lv_obj_t* btn = lv_btn_create(parent, NULL);
    switch(Btn_style){
      case btn_style_mustang:
        lv_btn_set_style(btn, LV_BTN_STYLE_REL, &btn_style_mustang_rel);
        lv_btn_set_style(btn, LV_BTN_STATE_PR, &btn_style_mustang_pr);
        break;
    }

    lv_obj_set_pos(btn, x, y);
    lv_obj_set_size(btn, width, height);
    lv_obj_set_free_num(btn, id);

    lv_obj_t* label = lv_label_create(btn, NULL);
    lv_label_set_text(label, text);
    lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);

    return btn;
}

void show(lv_obj_t* page) { lv_obj_set_hidden(page, false); }
void hide(lv_obj_t* page) { lv_obj_set_hidden(page, true); }

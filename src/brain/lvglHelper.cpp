#include "brain/lvglHelper.hpp"

static lv_style_t btn_style_mustang_rel;
static lv_style_t btn_style_mustang_pr;
static lv_style_t btn_style_blue_rel;
static lv_style_t btn_style_blue_pr;
static lv_style_t btn_style_red_rel;
static lv_style_t btn_style_red_pr;

static const lv_color_t MUSTANG_RED = LV_COLOR_MAKE(204+50, 32+50, 39+50);
static const lv_color_t MUSTANG_CHARCOAL = LV_COLOR_MAKE(65+50, 64+50, 66+50);
static const lv_color_t MUSTANG_LITE_GRAY = LV_COLOR_MAKE(184, 194, 192);

static const lv_color_t CRIMSON_RED = LV_COLOR_MAKE(153, 0, 0);
static const lv_color_t LIGHT_RED = LV_COLOR_MAKE(255, 100, 100);

lv_style_t make_style(lv_color_t main_color, lv_color_t border_color, lv_color_t text_color,
                      int radius, int border_width){
  lv_style_t style;
  lv_style_copy(&style, &lv_style_plain);
  style.body.main_color = main_color;
  style.body.grad_color = main_color;
  style.body.border.color = border_color;
  style.text.color = text_color;
  style.body.radius = radius;
  style.body.border.width = border_width;
  return style;
}

void init_button_styles(){
  btn_style_mustang_rel = make_style(LV_COLOR_RED, LV_COLOR_BLACK, LV_COLOR_WHITE, 10, 10);
  btn_style_mustang_pr = make_style(LV_COLOR_RED, LV_COLOR_WHITE, LV_COLOR_BLACK, 10, 10);

  btn_style_blue_rel = make_style(LV_COLOR_NAVY, LV_COLOR_BLUE, LV_COLOR_AQUA, 10, 10);
  btn_style_blue_pr = make_style(LV_COLOR_NAVY, LV_COLOR_AQUA, LV_COLOR_BLUE, 10, 10);

  btn_style_red_rel = make_style(LV_COLOR_RED, CRIMSON_RED, LV_COLOR_BLACK, 10, 10);
  btn_style_red_pr = make_style(LV_COLOR_RED, LIGHT_RED, CRIMSON_RED, 10, 10);
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
      case btn_style_blue:
        lv_btn_set_style(btn, LV_BTN_STYLE_REL, &btn_style_blue_rel);
        lv_btn_set_style(btn, LV_BTN_STATE_PR, &btn_style_blue_pr);
        break;
      case btn_style_red:
        lv_btn_set_style(btn, LV_BTN_STYLE_REL, &btn_style_red_rel);
        lv_btn_set_style(btn, LV_BTN_STATE_PR, &btn_style_red_pr);
        break;
    }

    lv_obj_set_pos(btn, x, y);
    lv_obj_set_size(btn, width, height);
    if (id != -1) lv_obj_set_free_num(btn, id);

    lv_obj_t* label = lv_label_create(btn, NULL);
    lv_label_set_text(label, text);
    lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);

    return btn;
}

void show(lv_obj_t* page) { lv_obj_set_hidden(page, false); }
void hide(lv_obj_t* page) { lv_obj_set_hidden(page, true); }

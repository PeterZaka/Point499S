#inlude "brainClasses/Style.hpp"

void setReleased(lv_color_t main_color, lv_color_t border_color, lv_color_t text_color,
                      int radius, int border_width){
  released = Style::make_style(main_color, border_color, text_color, radius, border_width);
}

void setPressed(lv_color_t main_color, lv_color_t border_color, lv_color_t text_color,
                      int radius, int border_width){
  pressed = Style::make_style(main_color, border_color, text_color, radius, border_width);
}

static make_style::Style(lv_color_t main_color, lv_color_t border_color, lv_color_t text_color,
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
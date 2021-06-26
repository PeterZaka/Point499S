#include "brain/lvglHelper.hpp"

lv_obj_t* createBtn(lv_obj_t* parent, lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height,
    const char* text, int id) {
    lv_obj_t* btn = lv_btn_create(parent, NULL);
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

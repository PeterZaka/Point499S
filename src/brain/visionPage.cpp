#include "brain/visionPage.hpp"

#define NO_COLOR LV_COLOR_TRANSP

static const double SCREENWIDTH = 450 - 20;
static const double SCREENHEIGHT = 210 - 20;
static const double WIDTHOFFSET = 100;
static const double HEIGHTOFFSET = 0;
static const double WIDTHRATIO = (SCREENWIDTH - WIDTHOFFSET) / VISION_FOV_WIDTH;
static const double HEIGHTRATIO = (SCREENHEIGHT - HEIGHTOFFSET) / VISION_FOV_HEIGHT;

static std::vector<Button> buttons;
static Style yellow_style;
static Style red_style;

static lv_obj_t* objectPositionLabel;
static lv_obj_t* objectSizeLabel;

static void update_vision(){
  if (!isAllInit) return;

  for (auto& btn: buttons) lv_obj_set_hidden(btn.lv_btn, true);

  for (int i = 0; i < vision.get_object_count(); i++){
     pros::vision_object_s_t object = vision.get_by_size(i);
     if (i >= buttons.size()) buttons.emplace_back(lv_scr_act(), 0, 0, 0, 0, "");
     Button btn = buttons[i];
     lv_obj_set_hidden(btn.lv_btn, false);

     if (object.signature == SIG_YELLOW.id) btn.setStyle(yellow_style);
     else if (object.signature == SIG_RED.id) btn.setStyle(red_style);
     lv_obj_set_pos(btn.lv_btn, (-(object.left_coord+object.width) + VISION_FOV_WIDTH) * WIDTHRATIO + WIDTHOFFSET, (-(object.top_coord+object.height) + VISION_FOV_HEIGHT) * HEIGHTRATIO + HEIGHTOFFSET);
     lv_obj_set_size(btn.lv_btn, object.width * WIDTHRATIO, object.height * HEIGHTRATIO);
  }

  if (vision.get_object_count() != 0) {
    pros::vision_object_s_t object = vision.get_by_size(0);
    lv_label_set_text(objectPositionLabel,
      ("(" + std::to_string(object.x_middle_coord) + ", " + std::to_string(object.y_middle_coord) + ")").c_str());
    lv_label_set_text(objectSizeLabel,
      ("(" + std::to_string(object.width) + ", " + std::to_string(object.height) + ")").c_str());
  }
}

pros::Task visionUpdateTask([]{
  while (true) {
    update_vision();
    pros::delay(50);
  }
});

void initalize_vision_page(lv_obj_t* visionPage){
  visionUpdateTask.suspend();

  objectPositionLabel = lv_label_create(visionPage, NULL);
  objectSizeLabel = lv_label_create(visionPage, NULL);
  lv_obj_align(objectPositionLabel, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 125);
  lv_obj_align(objectSizeLabel, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 150);

  yellow_style.setBoth(LV_COLOR_YELLOW, NO_COLOR, NO_COLOR, 0, 0);
  red_style.setBoth(LV_COLOR_RED, NO_COLOR, NO_COLOR, 0, 0);

}

void startVisionUpdateTask(){
  visionUpdateTask.resume();
}

void endVisionUpdateTask(){
  visionUpdateTask.suspend();

  for (auto& btn: buttons)lv_obj_set_hidden(btn.lv_btn, true);
}

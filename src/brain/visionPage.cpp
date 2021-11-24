#include "brain/visionPage.hpp"

#define NO_COLOR LV_COLOR_TRANSP

static const double SCREENWIDTH = 450;
static const double SCREENHEIGHT = 210;
static const double WIDTHOFFSET = 100;
static const double HEIGHTOFFSET = 0;
static const double WIDTHRATIO = (SCREENWIDTH - WIDTHOFFSET) / VISION_FOV_WIDTH;
static const double HEIGHTRATIO = (SCREENHEIGHT - HEIGHTOFFSET) / VISION_FOV_HEIGHT;

static std::vector<Button> buttons;
static Style yellow_style = Style();

static void update_vision(){
  for (int i = 0; i < vision.get_object_count(); i++){
     pros::vision_object_s_t object = vision.get_by_size(i);
     if (i >= buttons.size()) buttons.push_back(Button(lv_scr_act(), 0, 0, 0, 0, ""));
     Button btn = buttons[i];
     lv_obj_set_hidden(btn.lv_btn, false);

     if (object.signature == SIG_YELLOW.id) btn.setStyle(yellow_style);
     lv_obj_set_pos(btn.lv_btn, object.left_coord * WIDTHRATIO + WIDTHOFFSET, object.top_coord * HEIGHTRATIO + HEIGHTOFFSET);
     lv_obj_set_size(btn.lv_btn, object.width * WIDTHRATIO, object.height * HEIGHTRATIO);
  }
  for (int i = vision.get_object_count(); i < buttons.size(); i++){
    Button btn = buttons[i];
    lv_obj_set_hidden(btn.lv_btn, true);
  }
}

pros::Task visionUpdateTask([]{
  update_vision();
  pros::delay(250);
});

void initalize_vision_page(lv_obj_t* visionPage){
  visionUpdateTask.suspend();

  yellow_style.setBoth(LV_COLOR_YELLOW, NO_COLOR, NO_COLOR, 0, 0);

}

void startVisionUpdateTask(){
  visionUpdateTask.resume();
}

void endVisionUpdateTask(){
  visionUpdateTask.suspend();
}

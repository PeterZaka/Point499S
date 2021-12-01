#include "brain/odometryPage.hpp"

#define NO_COLOR LV_COLOR_TRANSP

static const double SCREENWIDTH = 450-120;
static const double SCREENHEIGHT = 210;
static const double WIDTHOFFSET = 120;
static const double HEIGHTOFFSET = 0;
static const double WIDTHRATIO = (SCREENWIDTH - WIDTHOFFSET) / 144;
static const double HEIGHTRATIO = (SCREENHEIGHT - HEIGHTOFFSET) / 144;

static Style yellow_tower_style;
static Style blue_tower_style;
static Style red_tower_style;
static Style tile1_style;
static Style tile2_style;
static Style platform_style;
static Style robot_style;

static lv_obj_t* robot;
static lv_obj_t* xPosLabel;
static lv_obj_t* yPosLabel;
static lv_obj_t* rotLabel;

static void update_odometry(){
  if (!isAllInit) return;

  lv_label_set_text(xPosLabel, ("x: " + std::to_string(xPos)).c_str());
  lv_label_set_text(yPosLabel, ("y: " + std::to_string(yPos)).c_str());
  lv_label_set_text(rotLabel, ("r: " + std::to_string(rot)).c_str());

  lv_obj_set_pos(robot, xPos * WIDTHRATIO + WIDTHOFFSET - 9, (-yPos+144) * HEIGHTRATIO + HEIGHTOFFSET - 9);
}

pros::Task odometryUpdateTask([]{
  while (true) {
    update_odometry();
    pros::delay(50);
  }
});

void initalize_odometry_page(lv_obj_t* odometryPage){
  odometryUpdateTask.suspend();

  xPosLabel = lv_label_create(odometryPage, NULL);
  yPosLabel = lv_label_create(odometryPage, NULL);
  rotLabel = lv_label_create(odometryPage, NULL);
  lv_obj_align(xPosLabel, NULL, LV_ALIGN_IN_TOP_LEFT, 310, 50);
  lv_obj_align(yPosLabel, NULL, LV_ALIGN_IN_TOP_LEFT, 310, 100);
  lv_obj_align(rotLabel, NULL, LV_ALIGN_IN_TOP_LEFT, 310, 150);

  yellow_tower_style.setBoth(LV_COLOR_YELLOW, NO_COLOR, NO_COLOR, 100, 0);
  blue_tower_style.setBoth(LV_COLOR_BLUE, NO_COLOR, NO_COLOR, 100, 0);
  red_tower_style.setBoth(LV_COLOR_RED, NO_COLOR, NO_COLOR, 100, 0);
  tile1_style.setBoth(LV_COLOR_GRAY, LV_COLOR_BLACK, NO_COLOR, 0, 1);
  tile2_style.setBoth(LV_COLOR_NAVY, LV_COLOR_BLACK, NO_COLOR, 0, 1);
  platform_style.setBoth(LV_COLOR_BLACK, LV_COLOR_BLACK, NO_COLOR, 0, 1);
  robot_style.setBoth(LV_COLOR_WHITE, LV_COLOR_BLACK, NO_COLOR, 100, 1);

  for (int i = 0; i < 6; i++){
    for (int j = 0; j < 6; j++){
      Button tile = Button(odometryPage, (144.0 / 6.0) * i * WIDTHRATIO + WIDTHOFFSET, (144.0 / 6.0) * j * HEIGHTRATIO + HEIGHTOFFSET,
                                          144.0 / 6.0 * WIDTHRATIO, 144.0 / 6.0 * HEIGHTRATIO, "");
      if ((i == 2 && j == 0) || (i == 3 && j == 0) || (i == 2 && j == 5) || (i == 3 && j == 5)) tile.setStyle(platform_style);
      else if ((i + j) % 2 == 0) tile.setStyle(tile1_style);
      else tile.setStyle(tile2_style);
    }
  }
  // yellow towers
  double tower_width_offset = 13.0 / 2.0;
  double tower_height_offset = 13.0 / 2.0;
  Button(odometryPage, 72 * WIDTHRATIO + WIDTHOFFSET - tower_width_offset, 72 * HEIGHTRATIO + HEIGHTOFFSET - tower_height_offset, 13 * WIDTHRATIO, 13 * HEIGHTRATIO, "").setStyle(yellow_tower_style);;
  Button(odometryPage, 36 * WIDTHRATIO + WIDTHOFFSET - tower_width_offset, 72 * HEIGHTRATIO + HEIGHTOFFSET - tower_height_offset, 13 * WIDTHRATIO, 13 * HEIGHTRATIO, "").setStyle(yellow_tower_style);
  Button(odometryPage, 108 * WIDTHRATIO + WIDTHOFFSET - tower_width_offset, 72 * HEIGHTRATIO + HEIGHTOFFSET - tower_height_offset, 13 * WIDTHRATIO, 13 * HEIGHTRATIO, "").setStyle(yellow_tower_style);
  // blue towers
  Button(odometryPage, 42 * WIDTHRATIO + WIDTHOFFSET - tower_width_offset, 132 * HEIGHTRATIO + HEIGHTOFFSET - tower_height_offset, 13 * WIDTHRATIO, 13 * HEIGHTRATIO, "").setStyle(blue_tower_style);
  Button(odometryPage, 136 * WIDTHRATIO + WIDTHOFFSET - tower_width_offset, 108 * HEIGHTRATIO + HEIGHTOFFSET - tower_height_offset, 13 * WIDTHRATIO, 13 * HEIGHTRATIO, "").setStyle(blue_tower_style);
  // red towers
  Button(odometryPage, 12 * WIDTHRATIO + WIDTHOFFSET - tower_width_offset, 36 * HEIGHTRATIO + HEIGHTOFFSET - tower_height_offset, 13 * WIDTHRATIO, 13 * HEIGHTRATIO, "").setStyle(red_tower_style);
  Button(odometryPage, 102 * WIDTHRATIO + WIDTHOFFSET - tower_width_offset, 12 * HEIGHTRATIO + HEIGHTOFFSET - tower_height_offset, 13 * WIDTHRATIO, 13 * HEIGHTRATIO, "").setStyle(red_tower_style);

  Button robot_button(odometryPage, 0, 0, 18 * WIDTHRATIO, 18 * HEIGHTRATIO, "");
  robot_button.setStyle(robot_style);
  robot = robot_button.lv_btn;

}

void startOdometryUpdateTask(){
  odometryUpdateTask.resume();
}

void endOdometryUpdateTask(){
  odometryUpdateTask.suspend();
}

#pragma once

#include "auton-config.hpp"
#include "robot-config.hpp"

#include <algorithm>

struct colorObject{
  colorObject(int x, int y, int w, int h) : x_cor(x), y_cor(y), width(w), height(h) {}

  int x_cor;
  int y_cor;
  int width;
  int height;
};

colorObject getLargestObject(pros::vision_signature sig, double timeAccumulate);

bool isColorDetected(pros::vision_signature sig);

void turnToColor(pros::vision_signature sig, double targetError, double targetTime);

void driveToColor(pros::vision_signature sig);

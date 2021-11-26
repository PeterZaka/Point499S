#pragma once

#include "auton-config.hpp"
#include "robot-config.hpp"

bool isColorDetected(pros::vision_signature sig);

void dirveToColor(pros::vision_signature sig);

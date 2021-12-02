#pragma once

#include "auton-config.hpp"
#include "robot-config.hpp"

bool isColorDetected(pros::vision_signature sig);

void turnToColor(pros::vision_signature sig, double targetError, double targetTime);

void driveToColor(pros::vision_signature sig);

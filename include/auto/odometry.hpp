#pragma once

#include "robot-config.hpp"
#include "chassis.hpp"

extern double wheelDiameter;
extern double wheelTrack;
extern double backDistance;

extern double xPos;
extern double yPos;
extern double rot;

void calculateOdom();

#pragma once

#include "robot-config.hpp"

extern double wheelDiameter;
extern double wheelTrack;
extern double backDistance;

extern double xPos;
extern double yPos;
extern double rot;
extern double calculatedRot;

extern double prevRot;

extern double deltaL;
extern double deltaR;
extern double deltaB;

void calculateOdom();

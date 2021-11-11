#pragma once

#include <math.h>
#include <algorithm>

double posMod(double x, double y);

double findShortestRotation(double start, double rotation);

double findRotationTo(double startX, double startY, double endX, double endY);

double findDistanceTo(double startX, double startY, double endX, double endY);

struct point {
  double x;
  double y;
};

point findOffsetTarget(point start, point target, point offset, double extraDistance=0);

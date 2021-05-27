#pragma once

#include <cmath>

#include "math.hpp"
#include "robot-config.hpp"
#include "chassis.hpp"

extern int driveTargetTime;
extern double driveTargetError;
extern int turnTargetTime;
extern double turnTargetError;

void goTo(double x, double y);

void driveForward(double distance);

void turnTo(double angle);

/*

  goToPoint(x, y);

  driveForward(12);

  turnTo(90);

  liftTo(far);
  liftTo(middle);
  liftTo(close);



*/

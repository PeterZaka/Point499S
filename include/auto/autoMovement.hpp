#pragma once

#include <cmath>

#include "math.hpp"
#include "robot-config.hpp"
#include "chassis.hpp"
#include "debug.hpp"
#include "auto/odometry.hpp"

extern int driveTargetTime;
extern double driveTargetError;
extern int turnTargetTime;
extern double turnTargetError;

enum movement{
  forward,
  backward,
  best
};

void goToPoint(double x, double y, movement Movement=forward);

void driveForward(double distance, double rotation=rot);
void driveToPoint(double x, double y, movement Movement=forward);

void turnToAngle(double angle);
void turnToPoint(double x, double y, movement Movement=forward);

// ----- helper functions -----

void findBestRotation(double& angle, movement& Movement);

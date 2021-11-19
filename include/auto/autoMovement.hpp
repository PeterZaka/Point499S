#pragma once

#include <cmath>

#include "math.hpp"
#include "robot-config.hpp"
#include "chassis.hpp"
#include "debug.hpp"
#include "auto/odometry.hpp"
#include "brain/pages.hpp"

extern double driveStrength; // 0 to 1 (0% to 100%)
extern int driveTargetTime; // amount of time (in milliseconds) needed within target error for driving
extern double driveTargetError; // be within distance (in inches) to be on target
extern int turnTargetTime; // amount of time (in milliseconds) needed within target error for turning
extern double turnTargetError; // be within distance (in degrees) to be on target
extern double correctRotationError; // be outside distance (in inches) to change rotation
extern double slowDownRotationError;

enum movement{
  forward,
  backward,
  best
};

void goToPoint(double x, double y, movement Movement=forward);

void driveForward(double distance, double rotation=rot);
void driveToPoint(double x, double y, movement Movement=best, double strength=5, bool isExponential=false, double angleClamp=200);

void turnToAngle(double angle);
void turnToAngle(double angle, double power);
void turnToPoint(double x, double y, movement Movement=forward);

void groupMoveTo(MotorGroup group, double pos, PID groupPID=PID(1,0,0), double targetError=50, double targetTime=10);
pros::Task groupMoveTo(MotorGroup group, double pos, double distanceToStart, PID groupPID=PID(1,0,0), double targetError=50, double targetTime=10);

void balance(PID balancePID);

void grabTower(point tower, movement Movement=forward, point offset={7, -9});

// ----- helper functions -----

void findBestRotation(double& angle, movement& Movement);

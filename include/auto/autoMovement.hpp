#pragma once

#include <cmath>

#include "math.hpp"
#include "debug.hpp"
#include "auton-config.hpp"
#include "robot-config.hpp"
#include "auto/odometry.hpp"

extern bool isAuton;

// ------- Drive -------
extern double prevDriveStrength;
extern double prevDriveTargetTime;
extern double prevDriveTargetError;
// Stop
extern double prevDriveStopTime;
extern double prevDriveStopError;
extern double prevDriveStopInterval;

// ------- Turn -------
extern double prevTurnTargetTime;
extern double prevTurnTargetError;
extern double prevCorrectRotationError;
extern double prevSlowDownRotationError;
// Stop
extern double prevTurnStopTime;
extern double prevTurnStopError;
extern double prevTurnStopInterval;

enum movement{
  forward,
  backward,
  best
};

void goToPoint(double x, double y, movement Movement=forward);

void driveForward(double distance, double rotation=rot);
void driveToPoint(double x, double y, movement Movement=best, double strength=3.5, double angleClamp=200);

void turnToAngle(double angle);
void turnToAngle(double angle, double power);
void turnToPoint(double x, double y, movement Movement=forward);

void groupMoveTo(MotorGroup group, double pos, PID groupPID=PID(1,0,0), double targetError=50, double targetTime=0.01);
pros::Task groupMoveTo(MotorGroup group, double pos, double distanceToStart, PID groupPID=PID(1,0,0), double targetError=50, double targetTime=0.01);

void balance(PID balancePID);

void grabTower(point tower, movement Movement=forward, point offset={1, 0});

bool doUntil(std::function<void()> Do, std::function<bool()> Until);
void waitUntil(std::function<bool()> Until);

// move to new file
void adjustToTower(movement Movement);

// ----- helper functions -----

void findBestRotation(double& angle, movement& Movement);

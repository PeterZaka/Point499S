#include "auto/autoMovement.hpp"

int driveTargetTime = 500;
double driveTargetError = 50;
int turnTargetTime = 500;
double turnTargetError = 3;

void goTo(double x, double y){
  OdomState position = chassis->getState();
  double angle = atan2f(
    ( y - position.y.convert(inch) ),
    ( x - position.x.convert(inch))
  );
  turnTo(angle);
  position = chassis->getState();

  double distance = sqrtf(
    pow ( ( x - position.x.convert(inch) ), 2.0) +
    pow ( ( y - position.y.convert(inch) ), 2.0)
  );
  driveForward(distance);
}

void driveForward(double distance){
  int timeOnTarget = 0;
  OdomState position = chassis->getState();
  double startX = position.x.convert(inch);
  double startY = position.y.convert(inch);
  drivePID.setTarget(distance);

  while (timeOnTarget < driveTargetTime){
    position = chassis->getState();
    double distanceFromStart = sqrtf(
      pow( ( startX - position.x.convert(inch) ), 2.0) +
      pow( ( startY - position.y.convert(inch) ), 2.0)
    );
    drivePID.update(distanceFromStart);
    // add in anglePID to drive straight
    leftSide.moveVoltage(drivePID.value() * 120.0);
    rightSide.moveVoltage(drivePID.value() * 120.0);

    if (abs(drivePID.error) < driveTargetError)
      timeOnTarget++;
    else
      timeOnTarget = 0;
    pros::delay(20);
  }
  leftSide.moveVoltage(0);
  rightSide.moveVoltage(0);
}

void turnTo(double angle){
  // add get rotation with inertial sensor
  int timeOnTarget = 0;
  double rotation = chassis->getState().theta.convert(degree);
  angle = findShortestRotation(rotation, angle);
  turnPID.setTarget(angle);

  while (timeOnTarget < turnTargetTime){
    rotation = chassis->getState().theta.convert(degree);
    turnPID.update(rotation);

    leftSide.moveVoltage(turnPID.value() * 120.0);
    rightSide.moveVoltage(-turnPID.value() * 120.0);

    if (abs(turnPID.error) < turnTargetError)
      timeOnTarget++;
    else
      timeOnTarget = 0;
    pros::delay(20);
  }
  leftSide.moveVoltage(0);
  rightSide.moveVoltage(0);
}

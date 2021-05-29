#include "auto/autoMovement.hpp"

int driveTargetTime = 500;
double driveTargetError = 3;
int turnTargetTime = 500;
double turnTargetError = 1;

void goTo(double x, double y){
  double angle = atan2f(
    ( y - yPos ),
    ( x - xPos )
  ) * (180 / pi);
  // convert counterclockwise to clockwise
  angle = -angle + 90;
  turnTo(angle);

  double distance = sqrtf(
    pow ( ( x - xPos ), 2.0) +
    pow ( ( y - yPos ), 2.0)
  );
  driveForward(distance);
}

void driveForward(double distance){
  int timeOnTarget = 0;
  double startX = xPos;
  double startY = yPos;
  drivePID.setTarget(distance);
  anglePID.setTarget(rot);

  while (timeOnTarget < driveTargetTime){
    double distanceFromStart = sqrtf(
      pow( ( startX - xPos ), 2.0) +
      pow( ( startY - yPos ), 2.0)
    );
    drivePID.update(distanceFromStart);
    anglePID.update(rot);

    leftSide.moveVoltage( (drivePID.value() + anglePID.value()) * 120.0);
    rightSide.moveVoltage( (drivePID.value() - anglePID.value()) * 120.0);

    if (abs(drivePID.error) < driveTargetError)
      timeOnTarget += 20;
    else
      timeOnTarget = 0;
    pros::delay(20);
  }
  leftSide.moveVoltage(0);
  rightSide.moveVoltage(0);
}

void turnTo(double angle){
  int timeOnTarget = 0;
  angle = findShortestRotation(rot, angle);
  turnPID.setTarget(angle);

  while (timeOnTarget < turnTargetTime){
    turnPID.update(rot);

    leftSide.moveVoltage(turnPID.value() * 120.0);
    rightSide.moveVoltage(-turnPID.value() * 120.0);

    if (abs(turnPID.error) < turnTargetError)
      timeOnTarget += 20;
    else
      timeOnTarget = 0;
    pros::delay(20);
  }
  leftSide.moveVoltage(0);
  rightSide.moveVoltage(0);
}

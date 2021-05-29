#include "auto/autoMovement.hpp"

int driveTargetTime = 500;
double driveTargetError = 3;
int turnTargetTime = 500;
double turnTargetError = 1;

void goTo(double x, double y, movement Movement){
  double angle = findRotationTo(xPos, yPos, x, y);

  if (Movement == backward){
    angle += 180;
  }
  if (Movement == best){
    double forwards = findShortestRotation(rot, angle);
    double backwards = findShortestRotation(rot, angle + 180);
    if (abs(rot - forwards) <= abs(rot - backwards)){
      Movement = forward;
      angle = forwards;
    } else {
      Movement = backward;
      angle = backwards;
    }
  }
  turnTo(angle);

  double distance = findDistanceTo(xPos, yPos, x, y);
  if (Movement == forward)
    driveForward(distance);
  else
    driveForward(-distance);
}

void driveForward(double distance){
  int timeOnTarget = 0;
  double startX = xPos;
  double startY = yPos;
  drivePID.setTarget(distance);
  anglePID.setTarget(rot);

  while (timeOnTarget < driveTargetTime){
    double distanceFromStart = findDistanceTo(xPos, yPos, startX, startY);
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

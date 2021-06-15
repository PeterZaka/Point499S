#include "auto/autoMovement.hpp"

int driveTargetTime = 500;
double driveTargetError = 1;
int turnTargetTime = 500;
double turnTargetError = 0.5;
double correctRotationError = 2;

void goToPoint(double x, double y, movement Movement){
  turnToPoint(x, y, Movement);
  driveToPoint(x, y);
}

void driveForward(double distance, double rotation){
  int timeOnTarget = 0;
  double startX = xPos;
  double startY = yPos;
  drivePID.setTarget(distance);
  anglePID.setTarget(rotation);

  bool isBackward = false;
  if (distance < 0) isBackward = true;

  while (timeOnTarget < driveTargetTime){
    double distanceFromStart = findDistanceTo(xPos, yPos, startX, startY);
    if (isBackward) distanceFromStart *= -1;

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

void driveToPoint(double x, double y){
  int timeOnTarget = 0;
  movement Movement = best;
  drivePID.reset();
  anglePID.reset();

  while (timeOnTarget < driveTargetTime){
    double distance = findDistanceTo(xPos, yPos, x, y);
    double rotation = findRotationTo(xPos, yPos, x, y);
    findBestRotation(rotation, Movement);
    if(Movement == backward) distance *= -1;

    drivePID.setTarget(distance, false);
    anglePID.setTarget(rotation, false);

    drivePID.update(0);
    anglePID.update(rot);
    if (abs(distance) > correctRotationError){
      leftSide.moveVoltage( (drivePID.value() + anglePID.value()) * 120.0);
      rightSide.moveVoltage( (drivePID.value() - anglePID.value()) * 120.0);
    } else {
      leftSide.moveVoltage(drivePID.value() * 120.0);
      rightSide.moveVoltage(drivePID.value() * 120.0);
    }

    if (abs(drivePID.error) < driveTargetError)
      timeOnTarget += 20;
    else
      timeOnTarget = 0;
    pros::delay(20);
  }
  leftSide.moveVoltage(0);
  rightSide.moveVoltage(0);
}

void turnToAngle(double angle){
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

void turnToPoint(double x, double y, movement Movement){
  double angle = findRotationTo(xPos, yPos, x, y);
  if (Movement == backward) angle += 180;
  if (Movement == best) findBestRotation(angle, Movement);
  turnToAngle(angle);
}

// ----- helper functions -----

void findBestRotation(double& angle, movement& Movement){
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

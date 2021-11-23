#include "auto/autoMovement.hpp"

double driveStrength = 1; // 0 to 1 (0% to 100%)
int driveTargetTime = 250; // amount of time (in milliseconds) needed within target error for driving
double driveTargetError = 3; // be within distance (in inches) to be on target
int turnTargetTime = 250; // amount of time (in milliseconds) needed within target error for turning
double turnTargetError = 1; // be within distance (in degrees) to be on target
double correctRotationError = 3; // be outside distance (in inches) to change rotation
double slowDownRotationError = 8;

void goToPoint(double x, double y, movement Movement){
  turnToPoint(x, y, Movement);
  driveToPoint(x, y, Movement);
}

void driveForward(double distance, double rotation){
  int timeOnTarget = 0;
  double startX = xPos;
  double startY = yPos;
  drivePID.setTarget(distance);
  anglePID.setTarget(rotation);
  // if (isDebugging){
  //   printf("\ndriveForward - Start: (%.2lf, %.2lf, %.2lf)\n", xPos, yPos, rot);
  //   printf("Target: %.2lf in, %.2lf rot)\n", distance, rotation);
  // }

  bool isBackward = false;
  if (distance < 0) isBackward = true;

  while (timeOnTarget < driveTargetTime){
    double distanceFromStart = findDistanceTo(xPos, yPos, startX, startY);
    if (isBackward) distanceFromStart *= -1;

    drivePID.update(distanceFromStart);
    anglePID.update(rot);
    leftSide.moveVoltage( (drivePID.value() + anglePID.value()) * 120.0 * driveStrength);
    rightSide.moveVoltage( (drivePID.value() - anglePID.value()) * 120.0 * driveStrength);

    if (abs(drivePID.error) < driveTargetError)
      timeOnTarget += 20;
    else
      timeOnTarget = 0;
    pros::delay(20);
  }
  leftSide.moveVoltage(0);
  rightSide.moveVoltage(0);
  // if (isDebugging) printf("End: (%.2lf, %.2lf, %.2lf)\n", xPos, yPos, rot);
}

void driveToPoint(double x, double y, movement Movement, double strength, bool isExponential, double angleClamp){
  int timeOnTarget = 0;
  movement prevBestMovement = best;
  movement bestMovement = best;
  drivePID.reset();
  // if (isDebugging){
  //   printf("\ndrivetoPoint - Start: (%.2lf, %.2lf, %.2lf)\n", xPos, yPos, rot);
  //   printf("Target: (%.2lf, %.2lf)\n", x, y);
  // }

  double prevRotation;
  while (timeOnTarget < driveTargetTime){
    double distance = findDistanceTo(xPos, yPos, x, y);
    double rotation = findRotationTo(xPos, yPos, x, y);

    findBestRotation(rotation, bestMovement);
    if( (abs(distance) < driveTargetError) && (bestMovement != prevBestMovement) ) // if passed target
        Movement = best;

    prevBestMovement = bestMovement;

    if ( (Movement == best) && (bestMovement == backward) ) {
      distance *= -1;
    } else if (Movement == forward) {
      rotation = findRotationTo(xPos, yPos, x, y);
      rotation = findShortestRotation(rot, rotation);
    } else if (Movement == backward) {
      rotation = findRotationTo(xPos, yPos, x, y);
      rotation = findShortestRotation(rot, rotation + 180);
      distance *= -1;
    }

    drivePID.setTarget(distance, false);
    drivePID.update(0);

    if (abs(distance) > correctRotationError){
      double strengthValue = strength * (rotation - rot);
      if(isExponential)
      {
        if(strengthValue < 0) strengthValue *= -strengthValue;
        else strengthValue *= strengthValue;
      }
      // if (abs(rotation - rot) > 45) strengthValue *= 5;
      // std::cout << strengthValue << std::endl;
      strengthValue = std::clamp(strengthValue, -angleClamp, angleClamp);
      if (abs(distance) <= slowDownRotationError) strengthValue *= 0.1;

      leftSide.moveVoltage( std::clamp( (drivePID.value() + strengthValue) * 120.0, -12000.0, 12000.0)  * driveStrength);
      rightSide.moveVoltage( std::clamp( (drivePID.value() - strengthValue) * 120.0, -12000.0, 12000.0)  * driveStrength);

    } else {
      leftSide.moveVoltage( std::clamp( (drivePID.value()) * 120.0, -12000.0, 12000.0)  * driveStrength);
      rightSide.moveVoltage( std::clamp( (drivePID.value()) * 120.0, -12000.0, 12000.0)  * driveStrength);
    }

    if (abs(drivePID.error) < driveTargetError)
      timeOnTarget += 20;
    else
      timeOnTarget = 0;
    pros::delay(20);
  }
  leftSide.moveVoltage(0);
  rightSide.moveVoltage(0);
  // if (isDebugging) printf("End: (%.2lf, %.2lf, %.2lf)\n", xPos, yPos, rot);
}

void turnToAngle(double angle){
  int timeOnTarget = 0;
  angle = findShortestRotation(rot, angle);
  turnPID.setTarget(angle);
  // if (isDebugging){
  //   printf("\nturnToAngle - Start: %.2lf\n", rot);
  //   printf("Target: %.2lf rot\n", angle);
  // }

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

  // if (isDebugging) printf("End: %.2lf\n", rot);
}

void turnToAngle(double angle, double power){
  angle = findShortestRotation(rot, angle);
  if (rot > angle) {
    leftSide.moveVoltage(-12000.0 * power);
    rightSide.moveVoltage(12000.0 * power);
    while (rot > angle) pros::delay(20);
  } else {
    leftSide.moveVoltage(12000.0 * power);
    rightSide.moveVoltage(-12000.0 * power);
    while (rot < angle) pros::delay(20);
  }
  leftSide.moveVoltage(0);
  rightSide.moveVoltage(0);
}

void turnToPoint(double x, double y, movement Movement){
  double angle = findRotationTo(xPos, yPos, x, y);
  // if (isDebugging){
  //   printf("\nturnToPoint - Start: (%.2lf, %.2lf, %.2lf)\n", xPos, yPos, rot);
  //   printf("Target: (%.2lf, %.2lf, %.2lf)\n", x, y, angle);
  // }
  if (Movement == backward) angle += 180;
  if (Movement == best) findBestRotation(angle, Movement);
  turnToAngle(angle);
}

void groupMoveTo(MotorGroup group, double pos, PID groupPID, double targetError, double targetTime){
  double timeOnTarget = 0;
  groupPID.setTarget(pos);

  while (timeOnTarget < targetTime){
    groupPID.update(group.getPosition());
    group.moveVoltage(groupPID.value() * 120.0);

    if (abs(groupPID.error) < targetError)
      timeOnTarget += 20;
    else
      timeOnTarget = 0;
    pros::delay(20);
  }
  group.moveVoltage(0);
}

pros::Task groupMoveTo(MotorGroup group, double pos, double distanceToStart, PID groupPID, double targetError, double targetTime){
  double startPosX = xPos;
  double startPosY = yPos;

  pros::Task startTurn([=]()
  {
    while(findDistanceTo(startPosX, startPosY, xPos, yPos) < distanceToStart) pros::delay(20);
    groupMoveTo(group, pos, groupPID, targetError, targetTime);
  });
  return startTurn;
}

void balance(PID balancePID){
  // add angle correction?
  balancePID.setTarget(0);
  while(true){
    balancePID.update(iSensor.get_pitch());

    if (abs(balancePID.value()) > 5) {
      leftSide.moveVoltage( balancePID.value() * 120.0);
      rightSide.moveVoltage( balancePID.value() * 120.0);
    } else {
      leftSide.moveVoltage(0);
      rightSide.moveVoltage(0);
    }

    pros::delay(20);
  }
  leftSide.moveVoltage(0);
  rightSide.moveVoltage(0);
}

void grabTower(point tower, movement Movement, point offset){
  int prevDriveTargetTime = driveTargetTime; driveTargetTime = 1;
  point point1 = findOffsetTarget({xPos, yPos}, tower, offset);
  driveToPoint(point1.x, point1.y, Movement);
  // point tower1 = findOffsetTarget({xPos, yPos}, tower, {7, 0});
  // double angle = findRotationTo(xPos, yPos, tower1.x, tower1.y);
  // angle = findShortestRotation(rot, angle);
  // if (Movement == forward) turnToAngle(angle);
  // if (Movement == backward) turnToAngle(angle + 180);
  driveTargetTime = prevDriveTargetTime;
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

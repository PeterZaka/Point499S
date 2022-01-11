#include "auto/autoMovement.hpp"

// ------- Drive -------
double prevDriveStrength = driveStrength;
double prevDriveTargetTime = driveTargetTime;
double prevDriveTargetError = driveTargetError;
// Stop
double prevDriveStopTime = driveStopTime;
double prevDriveStopError = driveStopError;
double prevDriveStopInterval = driveStopInterval;

// ------- Turn -------
double prevTurnTargetTime = turnTargetTime;
double prevTurnTargetError = turnTargetError;
double prevCorrectRotationError = correctRotationError;
double prevSlowDownRotationError = slowDownRotationError;
// Stop
double prevTurnStopTime = turnStopTime;
double prevTurnStopError = turnStopError;
double prevTurnStopInterval = turnStopInterval;

void goToPoint(double x, double y, movement Movement){
  turnToPoint(x, y, Movement);
  driveToPoint(x, y, Movement);
}

void driveForward(double distance, double rotation){
  double timeOnTarget = 0;
  double timeStopped = 0;
  double prevXPos = xPos;
  double prevYPos = yPos;
  double startX = xPos;
  double startY = yPos;
  drivePID.setTarget(distance);
  anglePID.setTarget(rotation);
  if (DebugDriveForward){
    printf("\ndriveForward - Start: (%.2lf, %.2lf, %.2lf)\n", xPos, yPos, rot);
    printf("Target: %.2lf in, %.2lf rot)\n", distance, rotation);
  }

  bool isBackward = false;
  if (distance < 0) isBackward = true;

  double timePassed = 0;
  while (timeOnTarget <= driveTargetTime && timeStopped <= driveStopTime){
    double distanceFromStart = findDistanceTo(xPos, yPos, startX, startY);
    if (isBackward) distanceFromStart *= -1;

    drivePID.update(distanceFromStart);
    anglePID.update(rot);
    leftSide.moveVoltage( (drivePID.value() + anglePID.value()) * 120.0 * driveStrength);
    rightSide.moveVoltage( (drivePID.value() - anglePID.value()) * 120.0 * driveStrength);

    if (abs(drivePID.error) < driveTargetError)
      timeOnTarget += 0.02;
    else
      timeOnTarget = 0;

    if (timePassed >= driveStopInterval){
      if (findDistanceTo(prevXPos, prevYPos, xPos, yPos) < driveStopError)
        timeStopped += timePassed;
      else
        timeStopped = 0;
      prevXPos = xPos;
      prevYPos = yPos;
      timePassed = 0;
    }

    timePassed += 0.02;
    pros::delay(20);
  }
  leftSide.moveVoltage(0);
  rightSide.moveVoltage(0);
  if (DebugDriveForward) {
    if (timeStopped > driveStopTime) printf("Stopped at: ");
    else printf("Reached target at: ");
    printf("(%.2lf, %.2lf, %.2lf)\n", xPos, yPos, rot);
  }
}

void driveToPoint(double x, double y, movement Movement, double strength, double angleClamp){
  double timeOnTarget = 0;
  double timeStopped = 0;
  double prevXPos = xPos;
  double prevYPos = yPos;
  movement prevBestMovement = best;
  movement bestMovement = best;
  drivePID.reset();
  if (DebugDriveToPoint){
    printf("\ndrivetoPoint - Start: (%.2lf, %.2lf, %.2lf)\n", xPos, yPos, rot);
    printf("Target: (%.2lf, %.2lf)\n", x, y);
  }

  double timePassed = 0;
  while (timeOnTarget <= driveTargetTime && timeStopped <= driveStopTime){
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
      strengthValue = std::clamp(strengthValue, -angleClamp, angleClamp);
      if (abs(distance) <= slowDownRotationError) strengthValue *= 0.1;

      leftSide.moveVoltage( std::clamp( (drivePID.value() + strengthValue) * 120.0, -12000.0, 12000.0)  * driveStrength);
      rightSide.moveVoltage( std::clamp( (drivePID.value() - strengthValue) * 120.0, -12000.0, 12000.0)  * driveStrength);

    } else {
      leftSide.moveVoltage( std::clamp( (drivePID.value()) * 120.0, -12000.0, 12000.0)  * driveStrength);
      rightSide.moveVoltage( std::clamp( (drivePID.value()) * 120.0, -12000.0, 12000.0)  * driveStrength);
    }

    if (abs(drivePID.error) < driveTargetError)
      timeOnTarget += 0.02;
    else
      timeOnTarget = 0;

    if (timePassed >= driveStopInterval){
      if (findDistanceTo(prevXPos, prevYPos, xPos, yPos) < driveStopError)
        timeStopped += timePassed;
      else
        timeStopped = 0;
      prevXPos = xPos;
      prevYPos = yPos;
      timePassed = 0;
    }

    timePassed += 0.02;
    pros::delay(20);
  }
  leftSide.moveVoltage(0);
  rightSide.moveVoltage(0);
  if (DebugDriveToPoint) {
    if (timeStopped > driveStopTime) printf("Stopped at: ");
    else printf("Reached target at: ");
    printf("(%.2lf, %.2lf, %.2lf)\n", xPos, yPos, rot);
  }
}

void turnToAngle(double angle){
  double timeOnTarget = 0;
  double timeStopped = 0;
  double prevRot = rot;
  angle = findShortestRotation(rot, angle);
  turnPID.setTarget(angle);
  if (DebugTurn){
    printf("\nturnToAngle - Start: %.2lf\n", rot);
    printf("Target: %.2lf rot\n", angle);
  }

  double timePassed = 0;
  while (timeOnTarget <= turnTargetTime && timeStopped <= turnStopTime){
    turnPID.update(rot);
    leftSide.moveVoltage(turnPID.value() * 120.0);
    rightSide.moveVoltage(-turnPID.value() * 120.0);

    if (abs(turnPID.error) < turnTargetError)
      timeOnTarget += 0.02;
    else
      timeOnTarget = 0;

    if (timePassed >= turnStopInterval){
      if (abs(prevRot - rot) < turnStopError)
        timeStopped += timePassed;
      else
        timeStopped = 0;
      prevRot = rot;
      timePassed = 0;
    }

    timePassed += 0.02;
    pros::delay(20);
  }
  leftSide.moveVoltage(0);
  rightSide.moveVoltage(0);

  if (DebugTurn) {
    if (timeStopped > driveStopTime) printf("Stopped at: ");
    else printf("Reached target at: ");
    printf("End: %.2lf\n", rot);
  }
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
  if (DebugTurn){
    printf("\nturnToPoint - Start: (%.2lf, %.2lf, %.2lf)\n", xPos, yPos, rot);
    printf("Target: (%.2lf, %.2lf, %.2lf)\n", x, y, angle);
  }
  if (Movement == backward) angle += 180;
  if (Movement == best) findBestRotation(angle, Movement);
  turnToAngle(angle);
}

void groupMoveTo(MotorGroup group, double pos, PID groupPID, double targetError, double targetTime){
  double timeOnTarget = 0;
  groupPID.setTarget(pos);

  if (DebugGroupMoveTo){
    printf("\ngroupMoveTo - Start: %.2lf\n", group.getPosition());
    printf("Target: %.2lf\n", pos);
  }
  while (timeOnTarget <= targetTime){
    groupPID.update(group.getPosition());
    group.moveVoltage(groupPID.value() * 120.0);

    if (abs(groupPID.error) < targetError)
      timeOnTarget += 0.02;
    else
      timeOnTarget = 0;
    pros::delay(20);
  }
  group.moveVoltage(0);

  if (DebugGroupMoveTo) printf("End: %.2lf\n", group.getPosition());
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
  driveTargetTime = 0;
  point point1 = findOffsetTarget({xPos, yPos}, tower, offset);
  driveToPoint(point1.x, point1.y, Movement);
  // point tower1 = findOffsetTarget({xPos, yPos}, tower, {7, 0});
  // double angle = findRotationTo(xPos, yPos, tower1.x, tower1.y);
  // angle = findShortestRotation(rot, angle);
  // if (Movement == forward) turnToAngle(angle);
  // if (Movement == backward) turnToAngle(angle + 180);
  driveTargetTime = prevDriveTargetTime;
}

void doUntil(std::function<void()> Do, std::function<bool()> Until){
  pros::Task doTask(Do);
  while (doTask.get_state() == pros::E_TASK_STATE_READY){
    if (Until()) doTask.remove();
    pros::delay(20);
  }
  doTask.remove();
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

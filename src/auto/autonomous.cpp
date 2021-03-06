#include "auto/autonomous.hpp"

#define t(x) [&]{x;}
#define r(x) [&]{return x;}


static void placeBackOnPlatform(double turning=0){
  lift.moveVoltage(12000);
  double beforeFunctionError = driveTargetError;
  driveTargetError = 1;
  driveForward(3);
  driveTargetError = beforeFunctionError;

  backArm.moveVoltage(-12000);
  waitUntil(r(backArmPot.get() < 350));
  lift.moveVoltage(0);

  if (turning == 0) {
    leftSide.moveVoltage(-12000 * 0.6);
    rightSide.moveVoltage(-12000 * 0.6);
  } else if (turning == -1) {
    leftSide.moveVoltage(-12000 * 0.8);
    rightSide.moveVoltage(-12000 * 0.2);
  }
  Wait(0.5);
  clawBack.set_value(false);
  Wait(0.1);
  lift.moveVoltage(12000);
  leftSide.moveVoltage(12000 * 0.2);
  rightSide.moveVoltage(12000 * 0.2);
  Wait(0.25);
  leftSide.moveVoltage(12000 * 0.6);
  rightSide.moveVoltage(12000 * 0.6);
  Wait(0.25);
  lift.moveVoltage(-12000);
  leftSide.moveVoltage(0);
  rightSide.moveVoltage(0);
}

static void placeFrontOnPlatform(){
  lift.moveVoltage(12000);
  double beforeFunctionError = driveTargetError;
  driveTargetError = 1;
  driveForward(-2);
  driveTargetError = beforeFunctionError;

  frontArm.moveVoltage(-12000);
  Wait(1);
  lift.moveVoltage(0);

  leftSide.moveVoltage(12000 * 0.6);
  rightSide.moveVoltage(12000 * 0.6);
  Wait(0.5);
  clawFront.set_value(false);
  leftSide.moveVoltage(12000 * -0.2);
  rightSide.moveVoltage(12000 * -0.2);
  Wait(0.25);
  leftSide.moveVoltage(12000 * -0.6);
  rightSide.moveVoltage(12000 * -0.6);
  Wait(0.25);
  leftSide.moveVoltage(12000 * -0.8);
  rightSide.moveVoltage(12000 * -0.8);
  Wait(0.25);
  lift.moveVoltage(-12000);
  leftSide.moveVoltage(0);
  rightSide.moveVoltage(0);
}

static void waitForClaw(){
  Wait(0.05); // move forward while claw is going down
  leftSide.moveVoltage(0); rightSide.moveVoltage(0);
  Wait(0.1); // ensure claw is in tower
}

void testAuton(){

  // doUntil(t(driveForward(10000)), r(false));

  leftAuton();

  // return;
  //
  // doUntil(t(driveForward(-24)), r(clawBackLeftButton.isPressed() || clawBackRightButton.isPressed()));
  // clawBack.set_value(true);
  // Wait(0.5);
  // backArm.moveVoltage(12000.0);
  // driveForward(24);

}

void rightAuton(){

  double startTime = pros::millis() / 1000.0;
  pros::Task autonTimerTask([&]{
    while (true) {
      autonTimer = pros::millis() / 1000.0 - startTime;
      if (autonTimer > 14.5) isAuton = false;
      pros::delay(20);
    }
  });


  xPos = 4.5 *24;
  yPos = 24 - 17.25/2.0;

  iSensor.set_rotation(180);
  rot = 180;
  prevRot = 180;

  bool gotLeftNeutral = false;
  bool gotMiddleNeutral = false;

  driveTargetTime = 0; // Don't stop

  backArm.moveVoltage(-12000);
  frontArm.moveVoltage(-12000);

  gotLeftNeutral = doUntil(t(grabTower({4.5 *24, 3 *24}, backward, {0, 0})), r(clawBackLeftButton.isPressed() || clawBackRightButton.isPressed()));
  clawBack.set_value(true);
  Wait(0.05); // move forward while claw is going down
  leftSide.moveVoltage(0); rightSide.moveVoltage(0);
  Wait(0.1); // ensure claw is in tower

  pros::Task checkBack([&]{
    backArm.moveVoltage(12000);
    double startTime = pros::millis() / 1000.0;
    while ((pros::millis() / 1000.0) - startTime < 1.5 && fabs(iSensor.get_pitch()) < 15) {
      if (!isAuton) return;
      pros::delay(20);
    }
    backArm.moveVoltage(-12000);
    while (true) {
      double startYPos = yPos;
      startTime = pros::millis() / 1000.0;
      while ((pros::millis() / 1000.0) - startTime < 3 && yPos > startYPos - 12) {
        if (!isAuton) return;
        pros::delay(20);
      }
      backArm.moveVoltage(12000);
      startTime = pros::millis() / 1000.0;
      while ((pros::millis() / 1000.0) - startTime < 1.5 && fabs(iSensor.get_pitch()) < 15) {
        if (!isAuton) return;
        pros::delay(20);
      }
      backArm.moveVoltage(-12000);
    }
  });


  while (backArmPot.get() < 800) {
    leftSide.moveVoltage(12000);
    rightSide.moveVoltage(12000);
    pros::delay(20);
  }

  checkBack.remove();
  backArm.moveVoltage(12000);
  driveStopError = 0; // Disable stop detection
  driveTargetError = 6;
  if (yPos < 1.5 *24) driveToPoint(xPos, 2 *24);

  point midTower = findOffsetTarget({xPos, yPos}, {3 *24, 3 *24}, {0, 0});
  gotMiddleNeutral = doUntil(t(driveToPoint(midTower.x, midTower.y, forward, 4)), r(clawFrontLeftButton.isPressed() || clawFrontRightButton.isPressed()));
  if (!gotMiddleNeutral) {
    driveForward(-12);
    turnTargetError = 3;
    turnToAngle(rot - 20);
    turnTargetError = prevTurnTargetError;
    gotMiddleNeutral = doUntil(t(driveForward(18)), r(clawFrontLeftButton.isPressed() || clawFrontRightButton.isPressed()));
    if (!gotMiddleNeutral) {
      driveForward(-18);
      turnTargetError = 3;
      turnToAngle(rot + 10);
      turnTargetError = prevTurnTargetError;
      gotMiddleNeutral = doUntil(t(driveForward(18)), r(clawFrontLeftButton.isPressed() || clawFrontRightButton.isPressed()));
    }
  }

  clawFront.set_value(true);
  Wait(0.1); // move forward while claw is going down
  leftSide.moveVoltage(0); rightSide.moveVoltage(0);
  Wait(0.1); // ensure claw is in tower
  frontArm.moveVoltage(0);

  if (!gotLeftNeutral && !gotMiddleNeutral) // miss both
  {
    std::cout << "miss both" << std::endl;

    backArm.moveVoltage(-12000);
    driveToPoint(5 *24, 2.75 *24);
    turnToAngle(180);
  }
  else if (!gotLeftNeutral && gotMiddleNeutral) // got mid, miss left
  {
    std::cout << "got mid, miss left" << std::endl;

    driveToPoint(5 *24, 1 *24);

  }
  else if (gotLeftNeutral && !gotMiddleNeutral) // got left, miss mid
  {
    std::cout << "got left, miss mid" << std::endl;

    driveToPoint(5 *24, 1 *24);
    turnToPoint(5 *24, 3 *24, forward);
  }
  else // got both
  {
    std::cout << "got both" << std::endl;

    driveToPoint(5 *24, 1 *24);
  }
}

void leftAuton(){

  double startTime = pros::millis() / 1000.0;
  pros::Task autonTimerTask([&]{
    while (true) {
      autonTimer = pros::millis() / 1000.0 - startTime;
      std::cout << autonTimer << std::endl;
      if (autonTimer > 14.5) {
        std::cout << "auton ended" << std::endl;
        isAuton = false;
        return;
      }
      pros::delay(200);
    }
  });


  xPos = 24 + 2.5;
	yPos = 24 - 17.25/2.0;

  iSensor.set_rotation(180);
  rot = 180;
  prevRot = 180;

  bool gotLeftNeutral = false;
  bool gotMiddleNeutral = false;

  // Go out of zone
  // miss both towers so get our alliance then put it in top and move as close as possible to center close to the opposite side with backward
  // X = 3 *24
  // y = 3.5 *24

  // Stay in zone for both
  // if get middle but miss left then put front arm down when (getting alliance tower with back arm) then go close to middle and face towards left
  // if get left but miss middle then grab alliance with front arm then get in position for middle and face middle

  driveTargetTime = 0; // Don't stop

  backArm.moveVoltage(-12000);
  frontArm.moveVoltage(-12000);

  gotLeftNeutral = doUntil(t(grabTower({1.5 *24, 3 *24}, backward, {-3.25, 0})), r(clawBackLeftButton.isPressed() || clawBackRightButton.isPressed()));
  if (!isAuton) return;
  clawBack.set_value(true);
  Wait(0.05); // move forward while claw is going down
  leftSide.moveVoltage(0); rightSide.moveVoltage(0);
  Wait(0.1); // ensure claw is in tower

  pros::Task checkBack([&]{
    backArm.moveVoltage(12000);
    double startTime = pros::millis() / 1000.0;
    while ((pros::millis() / 1000.0) - startTime < 1.5 && fabs(iSensor.get_pitch()) < 15) {
      if (!isAuton) return;
      pros::delay(20);
    }
    backArm.moveVoltage(-12000);
    while (true) {
      double startYPos = yPos;
      startTime = pros::millis() / 1000.0;
      while ((pros::millis() / 1000.0) - startTime < 3 && yPos > startYPos - 12) {
        if (!isAuton) return;
        pros::delay(20);
      }
      backArm.moveVoltage(12000);
      startTime = pros::millis() / 1000.0;
      while ((pros::millis() / 1000.0) - startTime < 1.5 && fabs(iSensor.get_pitch()) < 15) {
        if (!isAuton) return;
        pros::delay(20);
      }
      backArm.moveVoltage(-12000);
    }
  });


  while (backArmPot.get() < 800) {
    leftSide.moveVoltage(12000);
    rightSide.moveVoltage(12000);
    pros::delay(20);
  }

  checkBack.remove();
  backArm.moveVoltage(12000);

  leftSide.moveVoltage(12000 * 0.5);
  rightSide.moveVoltage(12000 * 0.5);
  Wait(0.1);
  leftSide.moveVoltage(12000 * 0.25);
  rightSide.moveVoltage(12000 * 0.25);
  Wait(0.1);
  leftSide.moveVoltage(12000 * 0);
  rightSide.moveVoltage(12000 * 0);
  while (backArmPot.get() < 1200) pros::delay(20);
  Wait(0.25);
  leftSide.moveVoltage(12000 * -0.25);
  rightSide.moveVoltage(12000 * -0.25);
  Wait(0.1);
  leftSide.moveVoltage(12000 * -0.5);
  rightSide.moveVoltage(12000 * -0.5);
  Wait(0.1);

  driveStopError = 0; // Disable stop detection
  driveTargetError = 6;
  if (yPos < 1 *24) driveToPoint(xPos, 1.5 *24);

  pros::Task frontArmAboveRings([&]{
    frontArm.moveVoltage(12000 * 0.2);
    Wait(0.1);
    while (findDistanceTo(xPos, yPos, 3 *24, 3 *24) > 36) {
      if (!isAuton) return;
      pros::delay(20);
    }
    frontArm.moveVoltage(-12000);
  });

  point midTower = findOffsetTarget({xPos, yPos}, {3 *24, 3 *24}, {-3, 0});
  gotMiddleNeutral = doUntil(t(driveToPoint(midTower.x, midTower.y, forward)), r(clawFrontLeftButton.isPressed() || clawFrontRightButton.isPressed()));
  if (!isAuton) return;
  //driveTargetError = prevDriveTargetError;
  if (!gotMiddleNeutral) {
    driveForward(-12);
    turnTargetError = 3;
    turnToAngle(rot - 16);
    turnTargetError = prevTurnTargetError;
    Wait(0.5);
    gotMiddleNeutral = doUntil(t(driveForward(18)), r(clawFrontLeftButton.isPressed() || clawFrontRightButton.isPressed()));
    if (!isAuton) return;
    if (!gotMiddleNeutral) {
      driveForward(-18);
      turnTargetError = 3;
      turnToAngle(rot + 20);
      turnTargetError = prevTurnTargetError;
      Wait(0.5);
      gotMiddleNeutral = doUntil(t(driveForward(18)), r(clawFrontLeftButton.isPressed() || clawFrontRightButton.isPressed()));
      if (!isAuton) return;
    }
  }

  clawFront.set_value(true);
  Wait(0.1); // move forward while claw is going down
  leftSide.moveVoltage(0); rightSide.moveVoltage(0);
  Wait(0.1); // ensure claw is in tower
  frontArm.moveVoltage(0);

  if (!gotLeftNeutral && !gotMiddleNeutral) // miss both
  {
    std::cout << "miss both" << std::endl;

    backArm.moveVoltage(-12000);
    driveToPoint(2 *24, 2.75 *24);
    turnToAngle(180);
  }
  else if (!gotLeftNeutral && gotMiddleNeutral) // got mid, miss left
  {
    std::cout << "got mid, miss left" << std::endl;

    driveToPoint(1 *24, 1 *24);

  }
  else if (gotLeftNeutral && !gotMiddleNeutral) // got left, miss mid
  {
    std::cout << "got left, miss mid" << std::endl;

    driveToPoint(1 *24, 1 *24);
    turnToPoint(3 *24, 3 *24, forward);
  }
  else // got both
  {
    std::cout << "got both" << std::endl;

    driveToPoint(1 *24, 1 *24);
  }
}

void leftMiddleAuton(){

  double startTime = pros::millis() / 1000.0;
  pros::Task autonTimerTask([&]{
    while (true) {
      autonTimer = pros::millis() / 1000.0 - startTime;
      std::cout << autonTimer << std::endl;
      if (autonTimer > 14.5) {
        std::cout << "auton ended" << std::endl;
        isAuton = false;
        return;
      }
      pros::delay(200);
    }
  });


  xPos = 24 + 2.5;
	yPos = 24 - 17.25/2.0;

  iSensor.set_rotation(findRotationTo(xPos, yPos, 24 *3, 24 *3));
  rot = findRotationTo(xPos, yPos, 24 *3, 24 *3);
  prevRot = findRotationTo(xPos, yPos, 24 *3, 24 *3);

  bool gotLeftNeutral = false;
  bool gotMiddleNeutral = false;

  driveTargetTime = 0; // Don't stop

  backArm.moveVoltage(-12000);
  frontArm.moveVoltage(-12000);

  gotMiddleNeutral = doUntil(t(grabTower({3 *24, 3 *24}, forward, {0.5, -2})), r(clawFrontLeftButton.isPressed() || clawFrontRightButton.isPressed()));
  if (!isAuton) return;
  clawFront.set_value(true);
  Wait(0.05); // move forward while claw is going down
  leftSide.moveVoltage(0); rightSide.moveVoltage(0);
  Wait(0.1); // ensure claw is in tower

  frontArm.moveVoltage(12000);

  leftSide.moveVoltage(-12000);
  rightSide.moveVoltage(-12000);

  while (yPos > 1.5*24) pros::delay(20);

  driveStopError = 0; // Disable stop detection
  driveTargetError = 6;

  pros::Task frontArmmm([&]{
    frontArm.moveVoltage(-12000);
    pros::delay(1000 * 2);
    frontArm.moveVoltage(12000 * 0.5);
  });

  point leftTower = findOffsetTarget({xPos, yPos}, {1.5 *24, 3 *24}, {-4, 0});
  gotLeftNeutral = doUntil(t(driveToPoint(leftTower.x, leftTower.y, backward)), r(clawBackLeftButton.isPressed() || clawBackRightButton.isPressed()));
  frontArm.moveVoltage(12000);
  if (!isAuton) return;
  //driveTargetError = prevDriveTargetError;
  if (!gotLeftNeutral) {
    driveForward(12);
    turnTargetError = 3;
    turnToAngle(rot + 8);
    turnTargetError = prevTurnTargetError;
    Wait(0.5);
    gotLeftNeutral = doUntil(t(driveForward(-18)), r(clawBackLeftButton.isPressed() || clawBackRightButton.isPressed()));
    if (!isAuton) return;
    if (!gotLeftNeutral) {
      driveForward(18);
      turnTargetError = 3;
      turnToAngle(rot - 16);
      turnTargetError = prevTurnTargetError;
      Wait(0.5);
      gotLeftNeutral = doUntil(t(driveForward(-18)), r(clawBackLeftButton.isPressed() || clawBackRightButton.isPressed()));
      if (!isAuton) return;
    }
  }

  backArm.moveVoltage(12000);

  clawBack.set_value(true);
  Wait(0.1); // move forward while claw is going down
  leftSide.moveVoltage(0); rightSide.moveVoltage(0);
  Wait(0.1); // ensure claw is in tower
  frontArm.moveVoltage(0);

  if (!gotLeftNeutral && !gotMiddleNeutral) // miss both
  {
    std::cout << "miss both" << std::endl;

    backArm.moveVoltage(-12000);
    driveToPoint(2 *24, 2.75 *24);
    turnToAngle(180);
  }
  else if (!gotLeftNeutral && gotMiddleNeutral) // got mid, miss left
  {
    std::cout << "got mid, miss left" << std::endl;

    driveToPoint(1 *24, 1 *24);

  }
  else if (gotLeftNeutral && !gotMiddleNeutral) // got left, miss mid
  {
    std::cout << "got left, miss mid" << std::endl;

    driveToPoint(1 *24, 1 *24);
    //turnToPoint(3 *24, 3 *24, forward);
  }
  else // got both
  {
    std::cout << "got both" << std::endl;

    driveToPoint(1 *24, 1 *24);
  }
}

void skills(){

  xPos = 24 - 17.25/2.0;
  yPos = 24/2.0;

  iSensor.set_rotation(90);
  rot = 90;
  prevRot = 90;

  driveTargetTime = 0;
  turnTargetTime = 0;

  driveTargetError = 6;

  drivePID.Kp = 20;

  pros::Task backArmHoldTask([&]{
    while(true){
      if (backArmPot.get() < 1700) backArm.moveVoltage(
        std::clamp(120 * (1700 - backArmPot.get()), 0.0, 12000.0));
      else backArm.moveVoltage(0);
      pros::delay(20);
    }
  });
  backArmHoldTask.suspend();

  // --------------------- SLIDE 1 ---------------------
  // 1: Get left red
  // 2: Get left neutral
  // 3: Score left neutral
  // 4: Score left red

  // 1: Get left red
  frontArm.moveVoltage(-12000);
  Wait(0.5);
  driveStrength = 0.3;
  doUntil(t(driveForward(18)), r(clawFrontLeftButton.isPressed() || clawFrontRightButton.isPressed()));
  driveStrength = 1;
  clawFront.set_value(true);
  waitForClaw();

  // 2: Get left neutral
  frontArm.moveVoltage(12000);
  Wait(0.5);
  backArm.moveVoltage(-12000);
  driveToPoint(1 *24, 1.25 *24, backward);
  doUntil(t(grabTower({1.5 *24, 3 *24}, backward, {-2, 0})), r(clawBackLeftButton.isPressed() || clawBackRightButton.isPressed()));
  clawBack.set_value(true);
  waitForClaw();
  backArmHoldTask.resume();

  // 3: Score left neutral
  driveToPoint(2.5 *24, 4 *24, backward);
  driveStopTime = 0;
  driveToPoint(2.85 *24, 5 *24, backward);
  driveStopTime = prevDriveStopTime;
  backArmHoldTask.suspend();
  placeBackOnPlatform(-1);
  backArm.moveVoltage(0);

  // 4: Score left red
  turnToPoint(3 *24, 5 *24, forward);
  driveForward(6);
  driveStopTime = 0;
  driveToPoint(3 *24, 5 *24, forward);
  driveStopTime = prevDriveStopTime;
  placeFrontOnPlatform();
  frontArm.moveVoltage(0);
  driveForward(-3);
  backArm.moveVoltage(-12000);


  // --------------------- SLIDE 2 ---------------------
  // Get left blue

  driveToPoint(5 *24, 4 *24, forward);
  doUntil(t(driveToPoint(4.15 *24, 5.5 *24, backward)), r(clawBackLeftButton.isPressed() || clawBackRightButton.isPressed()));
  lift.moveVoltage(0);
  clawBack.set_value(true);
  waitForClaw();
  backArmHoldTask.resume();

  // --------------------- SLIDE 3 ---------------------
  // Get right blue

  driveToPoint(5 *24, 4.15 *24);
  frontArm.moveVoltage(-12000);
  driveToPoint(2 *24, 4 *24, forward);
  doUntil(t(grabTower({0.5 *24, 4.5 *24}, forward, {1, 0})), r(clawFrontLeftButton.isPressed() || clawFrontRightButton.isPressed()));
  clawFront.set_value(true);
  waitForClaw();
  frontArm.moveVoltage(12000);
  Wait(0.25);


  // --------------------- SLIDE 4 ---------------------
  // 1: Score left blue
  // 2: Score right blue

  // 1: Score left blue
  driveToPoint(3 *24, 2 *24, backward);
  driveStopTime = 0;
  driveToPoint(3 *24, 1 *24, backward);
  driveStopTime = prevDriveStopTime;
  driveTargetError = 1;
  driveForward(1);
  driveTargetError = prevDriveTargetError;
  backArmHoldTask.suspend();
  placeBackOnPlatform();
  backArm.moveVoltage(0);

  // 2: Score right blue
  turnToPoint(3 *24, 1 *24, forward);
  driveForward(6);
  driveStopTime = 0;
  driveToPoint(3 *24, 1 *24, forward);
  driveStopTime = prevDriveStopTime;
  placeFrontOnPlatform();
  driveForward(-3);
  backArm.moveVoltage(-12000);
  Wait(2);

  // --------------------- SLIDE 5 ---------------------
  // 1: Get right red
  // 2: Get right neutral
  // 3: Score right neutral
  // 3: Score right red

  // 1: Get right red
  driveToPoint(4 *24, 1.5 *24, forward);
  turnToPoint(5.5 *24, 1.5 *24, forward);
  doUntil(t(driveToPoint(5.5 *24, 1.5 *24, forward)), r(clawFrontLeftButton.isPressed() || clawFrontRightButton.isPressed()));
  clawFront.set_value(true);
  waitForClaw();
  frontArm.moveVoltage(12000);
  Wait(0.25);

  // 2: Get right neutral
  turnToPoint(4.5 * 24, 3 *24, backward);
  doUntil(t(driveToPoint(4.5 *24, 3 *24, backward)), r(clawBackLeftButton.isPressed() || clawBackRightButton.isPressed()));
  clawBack.set_value(true);
  waitForClaw();
  backArmHoldTask.resume();

  // 3: Score right neutral
  driveToPoint(3 *24, 4 *24, backward);
  driveToPoint(3 *24, 5 *24, backward);
  backArmHoldTask.suspend();
  placeBackOnPlatform();
  backArm.moveVoltage(0);

  // 3: Score right red
  turnToPoint(3 *24, 5 *24, forward);
  driveForward(6);
  driveStopTime = 0;
  driveToPoint(3 *24, 1 *24, forward);
  driveStopTime = prevDriveStopTime;
  placeFrontOnPlatform();
  backArm.moveVoltage(12000);
  frontArm.moveVoltage(12000);
  driveForward(-3);


  // --------------------- SLIDE 6 ---------------------
  // 1: Push middle neutral

  // 1: Push middle neutral
  driveToPoint(5 *24, 5 *24);
  driveToPoint(2 *24, 2 *24);
}

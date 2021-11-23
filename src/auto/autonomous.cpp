#include "auto/autonomous.hpp"

void rightAuton(){

  yPos = 5;

  // Get First Tower
  groupMoveTo(clawFront, -1300, 0);
  // Drive to tower
  int prevDriveTargetTime = driveTargetTime; driveTargetTime = 1;
	driveToPoint(-1, 54.5, forward);
	driveTargetTime = prevDriveTargetTime;
  pros::delay(250);
  clawFront.moveVoltage(-12000.0);
  leftSide.moveVoltage(12000.0 * 0.05);
  rightSide.moveVoltage(12000.0 * 0.7);
  double startRot = rot;
  while (!(clawFrontButton.isPressed() || rot < startRot - 30)) pros::delay(20);
  leftSide.moveVoltage(0);
  rightSide.moveVoltage(0);
  pros::delay(250);
  clawFront.moveVoltage(12000.0);
  pros::delay(1000);

  // Part A: Get in position
  goToPoint(-2, 23.5, backward);
  lift.moveVoltage(-12000.0 * 0.9);
  turnToAngle(-87);
  // Part B: Drive and get tower in grip
  driveForward(-8, -87);
  groupMoveTo(clawBack, -2000);
  pros::delay(250);
  leftSide.moveVoltage(-12000.0 * 0.45);
  rightSide.moveVoltage(12000.0 * 0.1);
  int startTime = pros::millis();
  while (!(clawBackButton.isPressed() || pros::millis() > startTime + 2000)) pros::delay(20);
  leftSide.moveVoltage(0);
  rightSide.moveVoltage(0);
  // Part C: Secure tower in grip
  groupMoveTo(clawBack, -2200, 0);
  driveForward(-1);
  groupMoveTo(lift, 700, 0, PID(15, 0, 0), 50, 10000);
  pros::delay(500);

  // Drive to end position
  driveToPoint(-26, 24, best);
}

void leftAuton(){

  xPos = 29.5;
  // 15.5
	yPos = 15.5;

  // grabTower({36, 72});
  // return;

  // Get First Tower
  groupMoveTo(clawFront, -1300, 0);
  // Drive to tower
  int prevDriveTargetTime = driveTargetTime; driveTargetTime = 1;
	driveToPoint(8.5 + 29.5, 55.25 + 10.5, forward);
  // Turn into tower
  pros::delay(250);
  clawFront.moveVoltage(-12000.0);
  leftSide.moveVoltage(12000.0 * 0.05);
  rightSide.moveVoltage(12000.0 * 0.7);
  double startRot = rot;
  while (!(clawFrontButton.isPressed() || rot < startRot - 30)) pros::delay(20);
  leftSide.moveVoltage(0);
  rightSide.moveVoltage(0);
  pros::delay(250);
  clawFront.moveVoltage(12000.0);
  pros::delay(1000);

  // Get Middle Tower
  groupMoveTo(clawBack, -1700, 0);
  prevDriveTargetTime = driveTargetTime; driveTargetTime = 1;
  double prevTurnTargetError = turnTargetError; turnTargetError = 5;
  goToPoint(48, 58, backward);
  goToPoint(64, 58, backward);
  turnTargetError = prevTurnTargetError;
  lift.moveVoltage(-12000.0);
  // point tower1 = findOffsetTarget({xPos, yPos}, {72, 72}, {7, -10.5});
  // prevDriveTargetTime = driveTargetTime; driveTargetTime = 1;
  // turnToPoint(tower1.x, tower1.y, backward);
  grabTower({72, 72}, backward, {5, -10.5});
  // Turn into tower
  pros::delay(250);
  leftSide.moveVoltage(-12000.0 * 0.4);
  rightSide.moveVoltage(12000.0 * 0.1);
  clawBack.moveVoltage(-12000.0 * 0.125);
  int startTime = pros::millis();
  while (!(clawBackButton.isPressed() || pros::millis() > startTime + 3000)) pros::delay(20);
  leftSide.moveVoltage(0);
  rightSide.moveVoltage(0);
  pros::delay(1000);
  clawBack.moveVoltage(12000.0);
  pros::delay(1000);
  lift.moveVoltage(0);

  driveToPoint(10 + 29.5, 30 + 10.5);
  driveToPoint(0 + 29.5, 13 + 10.5);
  driveTargetTime = prevDriveTargetTime;
}

// Old Auton
// void leftAuton(){
//
//     yPos = 5;
//
//     // Get First Tower
//     groupMoveTo(clawFront, -1300, 0);
//     // Drive to tower
//     int prevDriveTargetTime = driveTargetTime; driveTargetTime = 1;
//   	driveToPoint(8.5, 55.25, forward);
//     // Turn into tower
//     pros::delay(250);
//     clawFront.moveVoltage(-12000.0);
//     leftSide.moveVoltage(12000.0 * 0.05);
//     rightSide.moveVoltage(12000.0 * 0.7);
//     double startRot = rot;
//     while (!(clawFrontButton.isPressed() || rot < startRot - 30)) pros::delay(20);
//     leftSide.moveVoltage(0);
//     rightSide.moveVoltage(0);
//     pros::delay(250);
//     clawFront.moveVoltage(12000.0);
//     pros::delay(1000);
//
//     // Get Middle Tower
//     groupMoveTo(clawBack, -2000, 0);
//     prevDriveTargetTime = driveTargetTime; driveTargetTime = 1;
//     goToPoint(25, 45, backward);
//     turnToPoint(50, 60, backward);
//     lift.moveVoltage(-12000.0);
//     driveForward(-findDistanceTo(xPos, yPos, 50, 60) + 2);
//     // Turn into tower
//     pros::delay(250);
//     leftSide.moveVoltage(-12000.0 * 0.3);
//     rightSide.moveVoltage(12000.0 * 0.05);
//     int startTime = pros::millis();
//     while (!(clawBackButton.isPressed() || pros::millis() > startTime + 3000)) pros::delay(20);
//     leftSide.moveVoltage(0);
//     rightSide.moveVoltage(0);
//     pros::delay(250);
//     clawBack.moveVoltage(12000.0);
//     pros::delay(1000);
//
//     driveToPoint(10, 30);
//     driveToPoint(0, 13);
//     driveTargetTime = prevDriveTargetTime;
// }

void driveTest(){
  driveForward(48);
}

void turnTest(){
  turnToAngle(90);
  turnToAngle(-90);
  turnToAngle(0);
  turnToAngle(-10);
  turnToAngle(-30);
  turnToAngle(0);
}

void diagonalTest(){
  driveToPoint(24, 24);
  driveToPoint(0, 0);
  turnToAngle(0);
}

void curveTest(){
  driveToPoint(24, 0, forward, 10);
  reset();
}

void reset(){
  goToPoint(0, 0);
  turnToAngle(0);
}

void skills(){

  // xPos = 72;
  // yPos = 96;

  xPos = 16;
  yPos = 10.5;

  iSensor.set_rotation(90);
  rot = 90;
  prevRot = 90 * (pi / 180);

  // Get left red
  groupMoveTo(clawFront, -1300, 0);
  lift.moveVoltage(-12000.0 * 0.9);
  driveForward(13);
  // Turn into tower
  pros::delay(250);
  clawFront.moveVoltage(-12000.0 * 0.25);
  leftSide.moveVoltage(12000.0 * 0.05);
  rightSide.moveVoltage(12000.0 * 0.5);
  double startRot = rot;
  while (!(clawFrontButton.isPressed() || rot < startRot - 80)) pros::delay(20);
  clawFront.moveVoltage(-12000.0);
  leftSide.moveVoltage(0);
  rightSide.moveVoltage(0);
  pros::Task liftTask = groupMoveTo(lift, 1000, 0, PID(0.1, 0.001, 0, 10000, -1), -1);
  pros::delay(250);

  // move left neutral tower to top right
  int prevDriveTargetTime = driveTargetTime; driveTargetTime = 1;
  driveForward(-10);
  // pros::delay(1000);
  driveToPoint(xPos + 2, yPos + 10, forward);
  //pros::delay(250);
  double angle = findRotationTo(xPos, yPos, 18, 60) + 180;
  turnToAngle(angle, 0.5);
  pros::delay(250);
  driveToPoint(18, 60, backward);
  driveTargetTime = 1000;
  double prevDriveTargetError = driveTargetError; driveTargetError = 30;
  double prevTurnTargetError = turnTargetError; turnTargetError = 3;
  turnToPoint(78, 110, backward);
  pros::Task speedTask([&](){
    driveStrength = 0.5;
    pros::delay(1000);
    driveStrength = 1;
  });
  driveToPoint(74, 112, backward);
  driveTargetError = prevDriveTargetError; driveTargetTime = 1;
  turnTargetError = prevTurnTargetError;
  liftTask.suspend();

  // score left red on platform
  driveToPoint(70, 100, forward);
  lift.moveVoltage(12000.0);
  turnToAngle(0);
  driveTargetTime = 1000;
  prevDriveTargetError = driveTargetError; driveTargetError = 25;
  driveForward(30);
  driveTargetError = prevDriveTargetError; driveTargetTime = 1;
  clawFront.moveVoltage(12000.0);
  pros::delay(1000);
  driveForward(-24);
  lift.moveVoltage(-12000.0);
  pros::delay(500);

  // get right blue
  groupMoveTo(clawFront, -1300, 0);
  turnToAngle(-90);
  driveForward(36);
  // driveToPoint(36, 114, forward);
  pros::Task moveTask([&](){
    grabTower({12, 108}, forward, {2, -6});
    while(true) pros::delay(1000);
  });
  pros::delay(2000);
  moveTask.suspend();
  leftSide.moveVoltage(12000.0 * -0.3);
  rightSide.moveVoltage(12000.0 * 0.5);
  while (rot > findShortestRotation(rot, -70) && !clawFrontButton.isPressed()) pros::delay(20);
  leftSide.moveVoltage(0);
  rightSide.moveVoltage(0);
  // Turn into tower
  // pros::delay(250);
  leftSide.moveVoltage(12000.0 * 0.05);
  rightSide.moveVoltage(12000.0 * 0.5);
  startRot = rot;
  while (!(clawFrontButton.isPressed() || rot < startRot - 80)) pros::delay(20);
  clawFront.moveVoltage(-12000.0);
  leftSide.moveVoltage(0);
  rightSide.moveVoltage(0);
  liftTask = groupMoveTo(lift, 1000, 0, PID(0.1, 0.001, 0, 10000, -1), -1);
  pros::delay(1000);
  // drive backwards after get tower

  // move middle neutral
  driveToPoint(48, 96, backward);
  driveToPoint(114, 36, backward);

  // score right blue on platform
  driveForward(24);
  driveToPoint(74, 48, forward);
  liftTask.suspend();
  lift.moveVoltage(12000.0);
  turnToAngle(180);
  driveTargetTime = 1000;
  prevDriveTargetError = driveTargetError; driveTargetError = 25;
  driveForward(30);
  driveTargetError = prevDriveTargetError; driveTargetTime = 1;
  clawFront.moveVoltage(12000.0);
  pros::delay(1000);
  driveToPoint(72, 50, backward);
  lift.moveVoltage(-12000.0);

  // get right red
  groupMoveTo(clawFront, -1300, 0);
  driveToPoint(100, 36, forward);
  driveTargetTime = 1000;
  prevDriveTargetError = driveTargetError; driveTargetError = 15;
  grabTower({132, 36}, forward, {2, -10});
  driveTargetError = prevDriveTargetError; driveTargetTime = 1;
  leftSide.moveVoltage(12000.0 * 0.05);
  rightSide.moveVoltage(12000.0 * 0.5);
  while (rot > findShortestRotation(rot, -90) && !clawFrontButton.isPressed()) pros::delay(20);
  leftSide.moveVoltage(0);
  rightSide.moveVoltage(0);
  // Turn into tower
  pros::delay(250);
  leftSide.moveVoltage(12000.0 * 0.05);
  rightSide.moveVoltage(12000.0 * 0.5);
  startRot = rot;
  while (!(clawFrontButton.isPressed() || rot < startRot - 80)) pros::delay(20);
  clawFront.moveVoltage(-12000.0);
  leftSide.moveVoltage(0);
  rightSide.moveVoltage(0);
  liftTask = groupMoveTo(lift, 1000, 0, PID(0.1, 0.001, 0, 10000, -1), -1);
  pros::delay(1000);

  // move right neutral
  driveToPoint(108, 48, backward);
  driveToPoint(108, 100, backward);

  // score right red on platform
  driveForward(5);
  driveToPoint(68, 96, forward);
  lift.moveVoltage(12000.0);
  turnToAngle(0);
  driveTargetTime = 1000;
  prevDriveTargetError = driveTargetError; driveTargetError = 25;
  driveForward(30);
  driveTargetError = prevDriveTargetError; driveTargetTime = 1;
  clawFront.moveVoltage(12000.0);
  pros::delay(1000);
  driveToPoint(72, 96, backward);
  lift.moveVoltage(-12000.0);
  pros::delay(10000);
}

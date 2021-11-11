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

  // xPos = 29.5;
	// yPos = 15.5;

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
  groupMoveTo(clawBack, -2000, 0);
  prevDriveTargetTime = driveTargetTime; driveTargetTime = 1;
  goToPoint(25 + 29.5, 45 + 10.5, backward);
  lift.moveVoltage(-12000.0);
  grabTower({72, 72}, backward);
  // Turn into tower
  pros::delay(250);
  leftSide.moveVoltage(-12000.0 * 0.3);
  rightSide.moveVoltage(12000.0 * 0.05);
  int startTime = pros::millis();
  while (!(clawBackButton.isPressed() || pros::millis() > startTime + 3000)) pros::delay(20);
  leftSide.moveVoltage(0);
  rightSide.moveVoltage(0);
  pros::delay(250);
  clawBack.moveVoltage(12000.0);
  pros::delay(1000);

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

  groupMoveTo(clawFront, -1300, 0);
  lift.moveVoltage(-12000.0 * 0.9);
  driveForward(15);

  // Turn into tower
  pros::delay(250);
  clawFront.moveVoltage(-12000.0);
  leftSide.moveVoltage(12000.0 * 0.05);
  rightSide.moveVoltage(12000.0 * 0.5);
  double startRot = rot;
  while (!(clawFrontButton.isPressed() || rot < startRot - 30)) pros::delay(20);
  clawFront.moveVoltage(0);
  leftSide.moveVoltage(0);
  rightSide.moveVoltage(0);
  pros::Task liftTask = groupMoveTo(lift, 1300, 0, PID(0.1, 0.001, 0, 10000, -1), -1);
  pros::delay(250);

  // move left neutral tower
  int prevDriveTargetTime = driveTargetTime; driveTargetTime = 1;
  driveForward(-10);
  pros::delay(1000);
  driveToPoint(xPos + 5, yPos + 10, forward);
  turnToAngle(180, 0.5);
  driveToPoint(24, 60, backward);
  driveToPoint(82, 110, backward);
  liftTask.suspend();

  // score
  driveToPoint(74, 100, forward);
  lift.moveVoltage(12000.0);
  turnToAngle(0);
  driveTargetTime = 1000;
  int prevDriveTargetError = driveTargetError; driveTargetError = 5;
  driveForward(23);
  driveTargetError = prevDriveTargetError; driveTargetTime = 1;
  clawFront.moveVoltage(12000.0);
  pros::delay(1000);
  driveToPoint(72, 96, backward);
  lift.moveVoltage(-12000.0);

  // get tower
  groupMoveTo(clawFront, -1300, 0);
  grabTower({12, 108}, forward, {2, -15});
  rightSide.moveVoltage(12000.0 * 0.5);
  while (rot > findShortestRotation(rot, -90)) pros::delay(20);
  rightSide.moveVoltage(0);
  // Turn into tower
  pros::delay(250);
  clawFront.moveVoltage(-12000.0);
  leftSide.moveVoltage(12000.0 * 0.05);
  rightSide.moveVoltage(12000.0 * 0.5);
  startRot = rot;
  while (!(clawFrontButton.isPressed() || rot < startRot - 30)) pros::delay(20);
  leftSide.moveVoltage(0);
  rightSide.moveVoltage(0);
  liftTask = groupMoveTo(lift, 1300, 0, PID(0.1, 0.001, 0, 10000, -1), -1);
  pros::delay(250);
  clawFront.moveVoltage(0);

  driveToPoint(60, 96, backward);
  driveToPoint(122, 24, backward);
}

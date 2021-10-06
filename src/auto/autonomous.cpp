#include "auto/autonomous.hpp"

void rightAuton(){
  // Get First Tower
  groupMoveTo(clawFront, -1300, 0);
  // Drive to tower
  int prevDriveTargetTime = driveTargetTime; driveTargetTime = 1;
	driveToPoint(-1, 55.5, forward);
	driveTargetTime = prevDriveTargetTime;
  // Turn into tower
  leftSide.moveVoltage(-12000.0);
  rightSide.moveVoltage(12000.0);
  while (rot > -7) pros::delay(20);
  leftSide.moveVoltage(0);
  rightSide.moveVoltage(0);
  pros::delay(250);
	groupMoveTo(clawFront, 0, 0, PID(1, 0, 0), 200, 100);
  pros::delay(250);

  // Part A: Get in position
  driveToPoint(0, 20, best);
  lift.moveVoltage(-12000.0 * 0.9);
  turnToAngle(-90);
  // Part B: Drive and get tower in grip
  driveForward(-9, -90);
  groupMoveTo(clawBack, -2000);
  turnTargetError = 30;
  turnToAngle(-120);
  turnTargetError = 2;
  // Part C: Secure tower in grip
  groupMoveTo(clawBack, -2200, 0);
  driveForward(-1);
  groupMoveTo(lift, 700, 0, PID(15, 0, 0), 50, 10000);
  pros::delay(500);

  // Drive to end position
  driveToPoint(-26, 24, best);
}

void leftAuton(){
  // Get First Tower
  groupMoveTo(clawFront, -1300, 0);
  // Drive to tower
  int prevDriveTargetTime = driveTargetTime; driveTargetTime = 1;
	driveToPoint(8, 55.5, forward);
	driveTargetTime = prevDriveTargetTime;
  // Turn into tower
  turnToAngle(-1, 0.5);
  groupMoveTo(clawFront, 0, PID(1, 0, 0), 200, 100);

  // Take down middle tower
  turnToAngle(-90);
  groupMoveTo(clawBack, -2000, 0);
  driveToPoint(38, 62, backward);
  turnToAngle(-70, 1);
  groupMoveTo(clawBack, 0, 0, PID(1, 0, 0), 200, 100);

  driveToPoint(-6, 5, backward);
  turnToAngle(-86);
  groupMoveTo(clawBack, -3000, 0);
  driveForward(-7, -86);
  driveForward(12, -90);
}

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

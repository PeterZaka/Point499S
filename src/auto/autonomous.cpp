#include "auto/autonomous.hpp"

void driveTest(){
  // Get First Tower
  groupMoveTo(clawFront, -1300, 0);
  // Drive to tower
  int prevDriveTargetTime = driveTargetTime; driveTargetTime = 1;
	driveToPoint(-1, 56, forward);
  driveTargetTime = prevDriveTargetTime;
  // Turn into tower
  leftSide.moveVoltage(12000.0); rightSide.moveVoltage(-12000.0);
  while(rot > -5) pros::delay(20);
  leftSide.moveVoltage(0); rightSide.moveVoltage(0);
  // Secure tower
	groupMoveTo(clawFront, 0, 0, PID(1, 0, 0), 200, 100);
  // pros::delay(500);

  // Get Second Tower
  // Part A: Get in position
  driveToPoint(0, 20.5, best);
  lift.moveVoltage(-12000.0 * 0.9);
  turnToAngle(-90);
  // Part B: Drive and get tower in grip
  driveForward(-9, -90);
  groupMoveTo(clawBack, -2000);
  turnTargetError = 20;
  turnToAngle(-120);
  turnTargetError = 2;
  // Part C: Secure tower in grip
  groupMoveTo(clawBack, -2200, 0);
  driveForward(-1); // (-1, -120)
  // Keep lift up
  groupMoveTo(lift, 700, 0, PID(15, 0, 0), 50, 10000);
  pros::delay(500);

  // Drive to end position
  driveToPoint(-26, 24, best);
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

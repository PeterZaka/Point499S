#include "auto/autonomous.hpp"

void rightAuton(){

  yPos = 5;

  // Get First Tower
  groupMoveTo(clawFront, -1300, 0);
  // Drive to tower
  int prevDriveTargetTime = driveTargetTime; driveTargetTime = 1;
	driveToPoint(-1, 54.5, forward);
	driveTargetTime = prevDriveTargetTime;
  clawFront.moveVoltage(-12000.0);
  pros::delay(250);
  // Turn into tower
  turnToAngle(-80, 1);
  pros::delay(500);
	groupMoveTo(clawFront, 0, PID(1, 0, 0), 200, 100);
  clawFront.moveVoltage(12000.0);

  // Part A: Get in position
  goToPoint(-2, 23.5, backward);
  lift.moveVoltage(-12000.0 * 0.9);
  turnToAngle(-90);
  // Part B: Drive and get tower in grip
  driveForward(-8, -90);
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

  yPos = 5;

  // Get First Tower
  groupMoveTo(clawFront, -1300, 0);
  // Drive to tower
  int prevDriveTargetTime = driveTargetTime; driveTargetTime = 1;
	driveToPoint(9, 55.25, forward);
	driveTargetTime = prevDriveTargetTime;
  clawFront.moveVoltage(-12000.0);
  // Turn into tower
  turnToAngle(-80, 1);
  pros::delay(500);
  groupMoveTo(clawFront, 0, PID(1, 0, 0), 200, 100);
  clawFront.moveVoltage(12000.0);

  // Take down middle tower
  turnToAngle(-90);
  groupMoveTo(clawBack, -1450, 0);
  driveToPoint(40, 61, backward);
  turnToAngle(-70, 1);
  driveForward(12);
  turnToPoint(-9, 7, backward);
  groupMoveTo(clawBack, 0, 0, PID(1, 0, 0), 200, 100);

  driveToPoint(-9, 7, backward);
  lift.moveVoltage(-12000.0 * 0.9);
  //turnToAngle(-77);
  turnToPoint(14, 6, backward);
  driveForward(-7);
  groupMoveTo(clawBack, -2400, PID(1, 0, 0), 200, 100);
  groupMoveTo(clawBack, -2200, 2, PID(1, 0, 0), 200, 100);
  driveForward(14);
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

#include "auto/autonomous.hpp"

void driveTest(){
  // Get First Tower
  groupMoveTo(clawFront, -1300, 24);
	driveToPoint(-1, 56, forward);
	turnToAngle(-10);
	groupMoveTo(clawFront, 0, PID(1, 0, 0), 600, 500);

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
  driveForward(-1, -120);
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

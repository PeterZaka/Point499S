#include "auto/autonomous.hpp"

void driveTest(){
  groupMoveTo(clawFront, -1300, 24);
	driveToPoint(0, 58, forward);
	turnToAngle(-10);
	groupMoveTo(clawFront, 0);
  // Got First Tower
  // driveToPoint(17, 48, best);
  // driveToPoint(17, 10, best);

  groupMoveTo(clawBack, -2000, 0);
  driveToPoint(0, 22, best);
  turnToAngle(-90);
  lift.moveVoltage(-12000.0);
  driveForward(-10, -90);
  turnToAngle(-100);
  groupMoveTo(lift, 300);
  // Got Second Tower

  driveToPoint(-26, 24, best);
}

void turnTest(){
  turnToAngle(90);
  turnToAngle(-90);
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

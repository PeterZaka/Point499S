#include "auto/autonomous.hpp"

void fullTestAuton(){
  goToPoint(24, 24, best);
  goToPoint(0, 0, best);
  turnToAngle(0);
}

void turnTestAuton(){
  turnToAngle(90);
  turnToAngle(100);
  turnToAngle(90);
  turnToAngle(95);
  turnToAngle(0);
  turnToAngle(180);
  turnToAngle(0);
}

void driveTestAuton(){
  driveForward(24, 0);
  driveForward(-12, 0);
  driveForward(5, 0);
  driveForward(-17, 0);
}

void driveToTestAuton(){
  driveToPoint(12, 24);
  driveToPoint(0, 0, backward);
}

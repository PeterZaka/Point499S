#include "auto/autonomous.hpp"

void fullTestAuton(){
  goToPoint(24, 24, forward);
  goToPoint(0, 0, backward);
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
  driveForward(24);
  driveForward(-12);
  driveForward(5);
  driveForward(-17);
}

void driveToTestAuton(){
  driveToPoint(12, 24);
  driveToPoint(0, 0, true);
}

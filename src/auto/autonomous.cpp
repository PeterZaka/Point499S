#include "auto/autonomous.hpp"

void fullTestAuton(){
  goTo(24, 24, forward);
  goTo(0, 0, backward);
  turnTo(0);
}

void turnTestAuton(){
  turnTo(90);
  turnTo(100);
  turnTo(90);
  turnTo(95);
  turnTo(0);
  turnTo(180);
  turnTo(0);
}

void driveTestAuton(){
  driveForward(24);
  driveForward(-12);
  driveForward(5);
  driveForward(-17);
}

void driveToTestAuton(){
  driveTo(12, 24);
  driveTo(0, 0, true);
}

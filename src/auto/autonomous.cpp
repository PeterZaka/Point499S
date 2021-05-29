#include "auto/autonomous.hpp"

void fullTestAuton(){
  goTo(24, 24);
  goTo(0, 0);
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

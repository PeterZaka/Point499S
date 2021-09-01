#include "auto/autonomous.hpp"

void driveTest(){
  driveForward(48);
  driveForward(48);
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
  driveToPoint(24, 0, forward);
  reset();
}

void reset(){
  goToPoint(0, 0);
  turnToAngle(0);
}

#include "auto/autonomous.hpp"

void driveTest(){
  goToPoint(0, 48, best);
  goToPoint(0, 0, best);
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

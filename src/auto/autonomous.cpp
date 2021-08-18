#include "auto/autonomous.hpp"

void test1(){
  goToPoint(24, 24, best);
  goToPoint(0, 0, best);
  turnToAngle(0);
}

void test2(){
  goToPoint(0, 24);
  goToPoint(24, 24);
  goToPoint(24, 0);
  goToPoint(0, 0);
  turnToAngle(0);

  // driveToPoint(24, 24, forward, 3, false, 70);
  // turnToAngle(90);
  // driveToPoint(0, 0, backward, 10, false, 80);
}

void test3(){
  driveTargetTime = 1;
  driveToPoint(24, 0, forward);
  reset();
  driveTargetTime = 500;
}

void test4(){
  turnToAngle(90);
  turnToAngle(-90);
  turnToAngle(0);
}

void reset(){
  goToPoint(0, 0);
  turnToAngle(0);
}

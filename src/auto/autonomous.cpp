#include "auto/autonomous.hpp"

void test1(){
  goToPoint(24, 24, best);
  goToPoint(0, 0, best);
  turnToAngle(0);
}

void test2(){
  driveToPoint(24, 24, forward, 3, false, 70);
  turnToAngle(90);
  driveToPoint(0, 0, backward, 10, false, 80);
}

void test3(){
  driveTargetTime = 1;
  driveToPoint(24, 0, forward);
  reset();

  driveToPoint(24, 0, forward, 10, false, 150);
  reset();

  driveToPoint(24, 0, forward, 10, false, 200);
  reset();

  driveToPoint(24, 0, forward, 2, true);
  reset();

  driveToPoint(24, 0, forward, 2, true, 150);
  reset();

  driveToPoint(24, 0, forward, 2, true, 200);
  reset();
  driveTargetTime = 500;
}

void test4(){
  driveTargetTime = 1;
  driveToPoint(24, 24, forward);
  reset();

  driveToPoint(24, 24, forward, 10, false, 150);
  reset();

  driveToPoint(24, 24, forward, 10, false, 200);
  reset();

  driveToPoint(24, 24, forward, 2, true);
  reset();

  driveToPoint(24, 24, forward, 2, true, 150);
  reset();

  driveToPoint(24, 24, forward, 2, true, 200);
  reset();
  driveTargetTime = 500;
}

void reset(){
  goToPoint(0, 0);
  turnToAngle(0);
}

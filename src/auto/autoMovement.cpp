#include "auto/autoMovement.hpp"

int driveTargetTime = 500;
double driveTargetError = 50;

void goToPoint(double x, double y){
  drivePID.value();
}

void driveForward(double distance){
  int timeOnTarget = 0;
  OdomState position = chassis->getState();
  double startX = position.x.convert(inch);
  double startY = position.y.convert(inch);
  drivePID.setTarget(distance);

  while(timeOnTarget < driveTargetTime){
    position = chassis->getState();
    double distanceFromStart = sqrtf(
      pow( ( startX - position.x.convert(inch) ), 2.0) +
      pow( ( startY - position.y.convert(inch) ), 2.0)
    );
    drivePID.update(distanceFromStart);
    // add in anglePID to drive straight
    leftSide.moveVoltage(drivePID.value() * 120.0);
    rightSide.moveVoltage(drivePID.value() * 120.0);

    if(abs(drivePID.error) < driveTargetError)
      timeOnTarget++;
    else
      timeOnTarget = 0;
    pros::delay(20);
  }
  leftSide.moveVoltage(0);
  rightSide.moveVoltage(0);
}

void turnTo(double angle){

}

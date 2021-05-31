#include "auto/odometry.hpp"

double wheelDiameter = 2.75;
double wheelTrack = 8;
double backDistance = 0.375;

double xPos = 0;
double yPos = 0;
double rot = 0;

static double prevLeft = 0;
static double prevRight = 0;
static double prevBack = 0;
static double prevRot = 0;

// https://github.com/OkapiLib/OkapiLib/blob/master/src/api/odometry/threeEncoderOdometry.cpp
void calculateOdom(){
  double deltaL = (leftEncoder.get() - prevLeft) / 360 * wheelDiameter * pi;
  double deltaR = (rightEncoder.get() - prevRight) / 360 * wheelDiameter * pi;
  double deltaB = (backEncoder.get() - prevBack) / 360 * wheelDiameter * pi;
  prevLeft = leftEncoder.get();
  prevRight = rightEncoder.get();
  prevBack = backEncoder.get();

  //double deltaTheta = (deltaL - deltaR) / wheelTrack;
  double deltaY = (deltaR + deltaL) / 2;
  double deltaX = deltaB;

  rot = iSensor.get_rotation() * (pi / 180);
  double deltaTheta = rot - prevRot;
  prevRot = rot;

  double localX;
  double localY;
  if (deltaTheta == 0){
    localX = deltaX;
    localY = deltaY;
  } else {
    localX = 2 * sin(deltaTheta / 2) *
      (deltaB / deltaTheta + backDistance);
    localY = 2 * sin(deltaTheta / 2) *
      (deltaR / deltaTheta + wheelTrack / 2);
  }

  // average rotation, same as (rot + prevRot) / 2
  double avgA = rot - (deltaTheta / 2);
  xPos += localX * cos(avgA) + localY * sin(avgA);
  yPos += -localX * sin(avgA) + localY * cos(avgA);
  rot = iSensor.get_rotation();
  //rot += deltaTheta;
}

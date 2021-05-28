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

  double deltaTheta = (deltaR - deltaL) / wheelTrack;
  double deltaY = (deltaR + deltaL) / 2;
  double deltaX = deltaB;

  double localX;
  double localY;
  if (deltaL == deltaR){
    localX = deltaX;
    localY = deltaY;
  } else {
    localX = 2 * sin(deltaTheta / 2) *
      (deltaX / deltaTheta + backDistance * 2);
    localY = 2 * sin(deltaTheta / 2) *
      (deltaR / deltaTheta + wheelTrack / 2);
  }

  double avgA = rot + (deltaTheta / 2);
  xPos += deltaX * cos(avgA) + deltaY * sin(avgA);
  yPos += -deltaX * sin(avgA) + deltaY * cos(avgA);
  rot += deltaTheta;
}

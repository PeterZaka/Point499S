#include "auto/odometry.hpp"

double wheelDiameter = 2.75;
double wheelTrack = 4.8888;
double backDistance = 4.2;

// 4.8888
// 4 and 3
// increase track

double xPos = 0;
double yPos = 0;
double rot = 0;
double calculatedRot = 0;

static double prevLeft = 0;
static double prevRight = 0;
static double prevBack = 0;
double prevRot = 0;

double deltaL = 0;
double deltaR = 0;
double deltaB = 0;


// https://github.com/OkapiLib/OkapiLib/blob/master/src/api/odometry/threeEncoderOdometry.cpp
void calculateOdom(){
  deltaL = (leftEncoder.get() - prevLeft) / 360 * wheelDiameter * pi;
  deltaR = (rightEncoder.get() - prevRight) / 360 * wheelDiameter * pi;
  deltaB = (backEncoder.get() - prevBack) / 360 * wheelDiameter * pi;
  prevLeft = leftEncoder.get();
  prevRight = rightEncoder.get();
  prevBack = backEncoder.get();

  calculatedRot += (deltaL - deltaR) / wheelTrack;
  double deltaY = (deltaR + deltaL) / 2;
  double deltaX = deltaB;

  rot = iSensor.get_rotation();
  if (deltaL == 0 && deltaR == 0 && deltaB == 0){
    iSensor.set_rotation(prevRot);
    rot = prevRot;
  }
  double deltaTheta = (rot - prevRot) * (pi / 180);

  // printf("%.2lf\n", deltaTheta);
  // printf("%.2lf\n\n", (deltaL - deltaR) / wheelTrack);

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
  double avgA = (rot + prevRot) * (pi / 180) / 2.0;
  xPos += localX * cos(avgA) + localY * sin(avgA);
  yPos += -localX * sin(avgA) + localY * cos(avgA);

  prevRot = rot;
  rot = iSensor.get_rotation();
  //rot += deltaTheta;
}

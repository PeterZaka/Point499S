#include "auto/autoVision.hpp"

bool isColorDetected(pros::vision_signature sig){
  for (int i = 0; i < vision.get_object_count(); i++){
    pros::vision_object_s_t object = vision.get_by_size(i);
    if (object.signature == sig.id) {
      return (object.width >= minColorWidth && object.height >= minColorHeight);
    }
  }
  return false;
}

void turnToColor(pros::vision_signature sig, double targetError, double targetTime){
  double timeOnTarget = 0;

  colorPID.setTarget(0);
  while (vision.get_object_count() != 0 && !clawFrontButton.isPressed() && timeOnTarget <= targetTime) {
    pros::vision_object_s_t object = vision.get_by_size(0);
    for (int i = 0; i < vision.get_object_count(); i++){
      object = vision.get_by_size(i);
      if (object.signature == sig.id && object.width >= minColorWidth && object.height >= minColorHeight) break;
    }
    if (!(object.signature == sig.id && object.width >= minColorWidth && object.height >= minColorHeight)) break;

    colorPID.update(object.x_middle_coord + VISION_FOV_WIDTH / 2);
    leftSide.moveVoltage( std::clamp( (colorPID.value() * colorStrength * 120.0), -12000.0, 12000.0));
    rightSide.moveVoltage( std::clamp( (colorPID.value() * colorStrength * 120.0), -12000.0, 12000.0));

    if (abs(object.x_middle_coord + VISION_FOV_WIDTH / 2) < targetError)
      timeOnTarget += 0.02;
    else
      timeOnTarget = 0;

    pros::delay(20);
  }
  leftSide.moveVoltage(0);
  rightSide.moveVoltage(0);
}

void dirveToColor(pros::vision_signature sig){
  colorPID.setTarget(0);
  while (vision.get_object_count() != 0 && !clawFrontButton.isPressed()) {
    pros::vision_object_s_t object = vision.get_by_size(0);
    for (int i = 0; i < vision.get_object_count(); i++){
      object = vision.get_by_size(i);
      if (object.signature == sig.id && object.width >= minColorWidth && object.height >= minColorHeight) break;
    }
    if (!(object.signature == sig.id && object.width >= minColorWidth && object.height >= minColorHeight)) break;

    colorPID.update(object.x_middle_coord + VISION_FOV_WIDTH / 2);
    leftSide.moveVoltage( std::clamp( 12000.0 + (colorPID.value() * colorStrength * 120.0), -12000.0, 12000.0));
    rightSide.moveVoltage( std::clamp( 12000.0 - (colorPID.value() * colorStrength * 120.0), -12000.0, 12000.0));

    pros::delay(20);
  }
  leftSide.moveVoltage(0);
  rightSide.moveVoltage(0);
}

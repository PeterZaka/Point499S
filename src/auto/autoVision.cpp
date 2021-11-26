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

void dirveToColor(pros::vision_signature sig){
  colorPID.setTarget(0);
  while (vision.get_object_count() != 0 && !clawFrontButton.isPressed()) {
    pros::vision_object_s_t object = vision.get_by_size(0);
    for (int i = 0; i < vision.get_object_count(); i++){
      object = vision.get_by_size(i);
      if (object.signature == sig.id) {
        if (object.width >= minColorWidth && object.height >= minColorHeight) break;
      }
    }
    if (object.signature != sig.id) break;

    colorPID.update(object.x_middle_coord);
    leftSide.moveVoltage( std::clamp( 12000.0 + (colorPID.value() * colorStrength * 120.0), -12000.0, 12000.0));
    rightSide.moveVoltage( std::clamp( 12000.0 - (colorPID.value() * colorStrength * 120.0), -12000.0, 12000.0));

    pros::delay(20);
  }
  leftSide.moveVoltage(0);
  rightSide.moveVoltage(0);
}

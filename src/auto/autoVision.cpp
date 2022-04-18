#include "auto/autoVision.hpp"

colorObject getLargestObject(pros::vision_signature sig, double timeAccumulate){
  std::vector<colorObject> validObjects = {};
  std::cout << "A";
  for(double time = 0; time <= timeAccumulate; time+=0.02){
    for (int i = 0; i < vision.get_object_count(); i++){
      pros::vision_object_s_t object = vision.get_by_size(i);
      if (object.signature == sig.id && object.width > minColorWidth && object.height > minColorHeight){
        validObjects.emplace_back((int)object.x_middle_coord, (int)object.y_middle_coord, (int)object.width, (int)object.height);
        break;
      }
    }
    pros::delay(20);
  }

  if (validObjects.size() == 0) return colorObject(0, 0, 0, 0);
  std::sort(validObjects.begin(), validObjects.end(), [](colorObject a, colorObject b){
    return ((a.width * a.height) > (b.width * b.height));
  });
  return validObjects[0];
}

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
  colorObject object = getLargestObject(SIG_YELLOW, 0.2);
  while (!clawFrontLeftButton.isPressed() && timeOnTarget <= targetTime) {
    colorPID.update((-object.x_cor + VISION_FOV_WIDTH) - (VISION_FOV_WIDTH / 2));
    leftSide.moveVoltage( std::clamp( (colorPID.value() * colorStrength * -120.0), -12000.0, 12000.0));
    rightSide.moveVoltage( std::clamp( (colorPID.value() * colorStrength * 120.0), -12000.0, 12000.0));

    if (abs((-object.x_cor + VISION_FOV_WIDTH) - (VISION_FOV_WIDTH / 2)) < targetError || object.width == 0)
      timeOnTarget += 0.05;
    else
      timeOnTarget = 0;

    object = getLargestObject(SIG_YELLOW, 0.05);
  }
  leftSide.moveVoltage(0);
  rightSide.moveVoltage(0);
}

void driveToColor(pros::vision_signature sig){
  colorPID.setTarget(0);
  while (vision.get_object_count() != 0 && !clawFrontLeftButton.isPressed()) {
    pros::vision_object_s_t object = vision.get_by_size(0);
    for (int i = 0; i < vision.get_object_count(); i++){
      object = vision.get_by_size(i);
      if (object.signature == sig.id && object.width >= minColorWidth && object.height >= minColorHeight) break;
    }
    if (!(object.signature == sig.id && object.width >= minColorWidth && object.height >= minColorHeight)) break;

    colorPID.update((-object.x_middle_coord + VISION_FOV_WIDTH) - (VISION_FOV_WIDTH / 2));
    leftSide.moveVoltage( std::clamp( 12000.0 - (colorPID.value() * colorStrength * 120.0), -12000.0, 12000.0));
    rightSide.moveVoltage( std::clamp( 12000.0 + (colorPID.value() * colorStrength * 120.0), -12000.0, 12000.0));

    pros::delay(20);
  }
  leftSide.moveVoltage(0);
  rightSide.moveVoltage(0);
}

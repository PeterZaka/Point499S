#include "chassis.hpp"

Motor topLeftMotor(10);
Motor topRightMotor(-19);
Motor backLeftMotor(-20);
Motor backRightMotor(9);

// Chassis Controller - lets us drive the robot around with open- or closed-loop control
std::shared_ptr<OdomChassisController> chassis =
  ChassisControllerBuilder()
      .withMotors(10, -19, -20, 9)
      .withDimensions(AbstractMotor::gearset::green, {{2.75_in, 12.5_in}, imev5GreenTPR})
      .withSensors(
          {'E', 'F', true},
          {'G', 'H'},
          {'A', 'B'})
      // specify the tracking wheels diameter (2.75 in), track (8 in),
      // specify the middle encoder distance (0.375 in) and diameter (2.75 in)
      .withOdometry({{2.75_in, 8_in, 0.375_in, 2.75_in}, quadEncoderTPR}, StateMode::CARTESIAN)
      .buildOdometry();

std::shared_ptr<XDriveModel> drive = std::dynamic_pointer_cast<XDriveModel>(chassis->getModel());

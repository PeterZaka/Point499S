#include "chassis.hpp"

// Chassis Controller - lets us drive the robot around with open- or closed-loop control
std::shared_ptr<OdomChassisController> chassis =
    ChassisControllerBuilder()
        .withMotors(10, -19, -20, 9)
        .withSensors(leftEncoder, rightEncoder, backEncoder)
        // specify the tracking wheels diameter (2.75 in), track (8 in),
        // specify the middle encoder distance (0.375 in) and diameter (2.75 in)
        .withDimensions(AbstractMotor::gearset::green, {{2.75_in, 8_in, 0.375_in, 2.75_in}, quadEncoderTPR})
        .withOdometry(StateMode::CARTESIAN)
        .buildOdometry();

std::shared_ptr<XDriveModel> drive = std::dynamic_pointer_cast<XDriveModel>(chassis->getModel());

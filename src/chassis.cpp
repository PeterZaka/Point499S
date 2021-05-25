#include "chassis.hpp"

// Chassis Controller - lets us drive the robot around with open- or closed-loop control
std::shared_ptr<ChassisController> chassis =
    ChassisControllerBuilder()
        .withMotors(10, -19, -20, 9)
				// Green gearset, 2.75 in wheel diam, 8 in wheel track
        .withDimensions(AbstractMotor::gearset::green, {{2.75_in, 8_in}, imev5GreenTPR})
        .withLogger(
        std::make_shared<Logger>(
            TimeUtilFactory::createDefault().getTimer(), // It needs a Timer
            "/ser/sout", // Output to the PROS terminal
            Logger::LogLevel::debug // Most verbose log level
        )
    )
        .build();

std::shared_ptr<XDriveModel> drive = std::dynamic_pointer_cast<XDriveModel>(chassis->getModel());

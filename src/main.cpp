#include "main.h"


void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}


void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}


void disabled() {}


void competition_initialize() {}


void autonomous() {}


// Chassis Controller - lets us drive the robot around with open- or closed-loop control
std::shared_ptr<ChassisController> chassis =
    ChassisControllerBuilder()
        .withMotors(10, -19, -20, 9)
				// Green gearset, 2.75 in wheel diam, 8 in wheel track
        .withDimensions(AbstractMotor::gearset::green, {{2.75_in, 8_in}, imev5GreenTPR})
        .build();
				
auto drive = std::dynamic_pointer_cast<XDriveModel>(chassis->getModel());

// Master controller by default
Controller controller;

void opcontrol() {

	while (true) {
		// Arcade drive with the left stick
		drive->xArcade(	controller.getAnalog(ControllerAnalog::leftX),
										controller.getAnalog(ControllerAnalog::leftY),
										controller.getAnalog(ControllerAnalog::rightX));

		pros::delay(10);
	}
}

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


void opcontrol() {
	// Chassis Controller - lets us drive the robot around with open- or closed-loop control
	std::shared_ptr<ChassisController> drive =
	    ChassisControllerBuilder()
	        .withMotors(11, -19, -20, 9)
					// Green gearset, 2.75 in wheel diam, 8 in wheel track
	        .withDimensions(AbstractMotor::gearset::green, {{2.75_in, 8_in}, imev5GreenTPR})
	        .build();

	// Master controller by default
  Controller controller;

	while (true) {
		// Arcade drive with the left stick
		drive->getModel()->arcade(controller.getAnalog(ControllerAnalog::leftY),
															controller.getAnalog(ControllerAnalog::leftX));

		pros::delay(10);
	}
}

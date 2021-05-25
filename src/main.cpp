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


void autonomous() {
	// Move 1 meter to the first goal
	chassis->moveDistance(12_in);
	// Turn 90 degrees to face second goal
	chassis->turnAngle(90_deg);
	// Drive 1 and a half feet toward second goal
	chassis->moveDistance(12_in);
}

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

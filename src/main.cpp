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

	pros::Task printTask([]()
		{
		while(1){
			printf("\n");
			printOdom();
			pros::delay(1000);
		}
		});

		fullTestAuton();
}

void opcontrol() {

	pros::Task printTask([]()
		{
		while(1){
			printf("\n");
			printOdom();
			pros::delay(1000);
		}
		});

	// Master controller by default
	Controller controller;

	ControllerButton fullTestButton(ControllerDigital::A);
	ControllerButton turnTestButton(ControllerDigital::Y);
	ControllerButton driveTestButton(ControllerDigital::X);

	while (true) {
		// Arcade drive with the left stick
		drive->xArcade(	controller.getAnalog(ControllerAnalog::leftX),
										controller.getAnalog(ControllerAnalog::leftY),
										controller.getAnalog(ControllerAnalog::rightX));

		if (fullTestButton.changedToPressed())
			fullTestAuton();
		else if (turnTestButton.changedToPressed())
			turnTestAuton();
		else if (driveTestButton.changedToPressed())
			driveTestAuton();

		pros::delay(10);
	}
}

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

	bool fieldCentric = false;

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
	ControllerButton fieldCentricButton(ControllerDigital::B);

	while (true) {
		if (fieldCentric == false){
			// Arcade drive with the left stick
			drive->xArcade(	controller.getAnalog(ControllerAnalog::leftX),
											controller.getAnalog(ControllerAnalog::leftY),
											controller.getAnalog(ControllerAnalog::rightX));
		} else {

			double yAxis = controller.getAnalog(ControllerAnalog::leftY) * 100;
			double xAxis = controller.getAnalog(ControllerAnalog::leftX) * 100;

			double joystickDirection = std::atan2(yAxis, xAxis);
			joystickDirection += chassis->getState().theta.convert(radian);

	    double maxPower = std::min(sqrt(pow(xAxis,2) + pow(yAxis,2)), 100.0) * 0.9;
	    double motorPower = maxPower / (fabs(sin(joystickDirection)) + fabs(cos(joystickDirection)));

	    // move
	    double tl = (sin(joystickDirection) + cos(joystickDirection)) * motorPower;
	    double bl = (sin(joystickDirection) - cos(joystickDirection)) * motorPower;
	    double tr = (sin(joystickDirection) - cos(joystickDirection)) * motorPower;
	    double br = (sin(joystickDirection) + cos(joystickDirection)) * motorPower;

	    // rotate
	    double clockwise = controller.getAnalog(ControllerAnalog::rightX);
	    if(fabs(clockwise) < 1) clockwise = 0;

	    maxPower = std::max(fabs(clockwise*100.0), maxPower);
	    tl += (maxPower - fabs(tl)) * clockwise;
	    bl += (maxPower - fabs(br)) * clockwise;
	    tr -= (maxPower - fabs(tr)) * clockwise;
	    br -= (maxPower - fabs(br)) * clockwise;

			Motor topLeftMotor(10);
			Motor topRightMotor(-19);
			Motor backLeftMotor(-20);
			Motor backRightMotor(9);

			topLeftMotor.moveVoltage(tl * 120);
			backLeftMotor.moveVoltage(bl * 120);
			topRightMotor.moveVoltage(tr * 120);
			backRightMotor.moveVoltage(br * 120);

		}


		if (fullTestButton.changedToPressed())
			fullTestAuton();
		else if (turnTestButton.changedToPressed())
			turnTestAuton();
		else if (driveTestButton.changedToPressed())
			driveTestAuton();

		if (fieldCentricButton.changedToPressed())
			fieldCentric = !fieldCentric;

		pros::delay(10);
	}
}

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


void printEncoders(){
	printf("\n------\n");
	printf("left encoder =\t %.2lf\n", leftEncoder.get());
	printf("right encoder =\t %.2lf\n", rightEncoder.get());
	printf("back encoder =\t %.2lf\n", backEncoder.get());
}

void printOdom(){
	OdomState odom = chassis->getState();
	printf("\n------\n");
	printf("x =\t %.2lf\n", odom.x.convert(inch));
	printf("y =\t %.2lf\n", odom.y.convert(inch));
	printf("rot =\t %.2lf\n", odom.theta.convert(degree));
}


void autonomous() {

	pros::Task printTask([]()
		{
		while(1){
			printf("\n");
			printOdom();
			pros::delay(1000);
		}
		});

	// set the state to zero
	chassis->setState({0_in, 0_in, 0_deg});

	chassis->turnToAngle(90_deg);

	chassis->turnToAngle(0_deg);
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

	while (true) {
		// Arcade drive with the left stick
		drive->xArcade(	controller.getAnalog(ControllerAnalog::leftX),
										controller.getAnalog(ControllerAnalog::leftY),
										controller.getAnalog(ControllerAnalog::rightX));

		pros::delay(10);
	}
}

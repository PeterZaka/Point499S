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
	Logger::setDefaultLogger(
    std::make_shared<Logger>(
        TimeUtilFactory::createDefault().getTimer(), // It needs a Timer
        "/ser/sout", // Output to the PROS terminal
        Logger::LogLevel::warn // Show errors and warnings
    )
);

	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}


void disabled() {}


void competition_initialize() {}


void autonomous() {

}

void opcontrol() {

	iSensor.reset();
	pros::delay(20);
	while(iSensor.is_calibrating()){
		printf("calibrating...\n");
		pros::delay(200);
	}
	printf("done calibrating\n");

	bool fieldCentric = false;

	pros::Task calculateOdomTask([]()
		{
		while(1){
			calculateOdom();
			pros::delay(10);
		}
		});

	/*pros::Task printTask([]()
		{
		while(1){
			printf("\n");
			printOdom();
			pros::delay(3000);
		}
		});
		*/

	// Master controller by default
	Controller controller;

	ControllerButton test1Button(ControllerDigital::A);
	ControllerButton test2Button(ControllerDigital::B);
	ControllerButton test3Button(ControllerDigital::Y);
	ControllerButton test4Button(ControllerDigital::X);
	ControllerButton balanceButton(ControllerDigital::down);

	ControllerButton fieldCentricButton(ControllerDigital::up);

	brainPrint("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

	while (true) {

		double yAxis = controller.getAnalog(ControllerAnalog::leftY);
		double xAxis = controller.getAnalog(ControllerAnalog::leftX);

		double joystickDirection = std::atan2(yAxis, xAxis);
		if (fieldCentric)
			joystickDirection += rot * (pi / 180);

    double maxPower = std::min(sqrt(pow(xAxis,2) + pow(yAxis,2)), 1.0) * 0.9;
    double motorPower = maxPower / (fabs(sin(joystickDirection)) + fabs(cos(joystickDirection)));

    // move
    double tl = (sin(joystickDirection) + cos(joystickDirection)) * motorPower;
    double bl = (sin(joystickDirection) - cos(joystickDirection)) * motorPower;
    double tr = (sin(joystickDirection) - cos(joystickDirection)) * motorPower;
    double br = (sin(joystickDirection) + cos(joystickDirection)) * motorPower;

    // rotate
    double clockwise = controller.getAnalog(ControllerAnalog::rightX);

    maxPower = std::max(fabs(clockwise), maxPower);
    tl += (maxPower - fabs(tl)) * clockwise;
    bl += (maxPower - fabs(br)) * clockwise;
    tr -= (maxPower - fabs(tr)) * clockwise;
    br -= (maxPower - fabs(br)) * clockwise;

		topLeftMotor.moveVoltage(tl * 12000);
		backLeftMotor.moveVoltage(bl * 12000);
		topRightMotor.moveVoltage(tr * 12000);
		backRightMotor.moveVoltage(br * 12000);


		if (test1Button.changedToPressed())
			test1();
		else if (test2Button.changedToPressed())
			test2();
		else if (test3Button.changedToPressed())
			test3();
		else if (test4Button.changedToPressed())
			test4();
		else if (balanceButton.changedToPressed())
			balance({5, 0, 0});

		if (fieldCentricButton.changedToPressed())
			fieldCentric = !fieldCentric;

		pros::delay(10);
	}
}

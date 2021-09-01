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
	autonSelectScreenInitialize();

	clawFront.setBrakeMode(AbstractMotor::brakeMode::hold);
	clawBack.setBrakeMode(AbstractMotor::brakeMode::hold);
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

	pros::Task calculateOdomTask([]()
		{
		while(1){
			calculateOdom();
			pros::delay(10);
		}
		});

	// pros::Task printTask([]()
	// 	{
	// 	while(1){
	// 		printf("\n");
	// 		std::cout << liftPower << std::endl;
	// 		pros::delay(3000);
	// 	}
	// 	});

	// Master controller by default
	Controller controller;

	ControllerButton liftUpButton(ControllerDigital::R1);
	ControllerButton liftDownButton(ControllerDigital::R2);
	ControllerButton clawFrontUpButton(ControllerDigital::L1);
	ControllerButton clawFrontDownButton(ControllerDigital::L2);
	ControllerButton clawBackUpButton(ControllerDigital::X);
	ControllerButton clawBackDownButton(ControllerDigital::B);

	bool isDrivingStraight = false;
	bool isLiftStopped = false;

	while (true) {
		double leftYAxis = controller.getAnalog(ControllerAnalog::leftY);
		double rightYAxis = controller.getAnalog(ControllerAnalog::rightY);
		if(abs(leftYAxis) < 0.1) leftYAxis = 0;
		if(abs(rightYAxis) < 0.1) rightYAxis = 0;

		if(abs(leftYAxis) > 0 && abs(rightYAxis) > 0 && // if moving jotsticks
		 (abs(leftYAxis - rightYAxis) < 0.1)){ // if joysticks in simillar range
			if(isDrivingStraight == false){
				isDrivingStraight = true;
				anglePID.setTarget(rot);
			} else {
				anglePID.update(rot);
			}
		} else {
			isDrivingStraight = false;
		}

		isDrivingStraight = false;

		if(isDrivingStraight){
			leftSide.moveVoltage((leftYAxis + anglePID.value() / 100.0) * 12000.0);
			rightSide.moveVoltage((leftYAxis - anglePID.value() / 100.0) * 12000.0);
		} else {
			leftSide.moveVoltage((leftYAxis) * 12000.0);
			rightSide.moveVoltage((rightYAxis) * 12000.0);
		}

		if(liftUpButton.isPressed()){
			lift.moveVoltage(12000.0 * liftPower);
			isLiftStopped = false;
		}
		else if(liftDownButton.isPressed()){
			lift.moveVoltage(-12000.0 * liftPower);
			isLiftStopped = false;
		}
		else {
			lift.moveVoltage(0.0);
		}

		if(clawFrontUpButton.isPressed()) clawFront.moveVoltage(12000.0 * 0.9);
		else if(clawFrontDownButton.isPressed()) clawFront.moveVoltage(-12000.0 * 0.9);
		else clawFront.moveVoltage(0);

		if(clawBackUpButton.isPressed()) clawBack.moveVoltage(12000.0 * 0.9);
		else if(clawBackDownButton.isPressed()) clawBack.moveVoltage(-12000.0 * 0.9);
		else clawBack.moveVoltage(0);

		switch (Test){
			case drive:
				pros::delay(3000);
				driveTest();
				break;
			case turn:
				pros::delay(3000);
				turnTest();
				break;
			case diagonal:
				pros::delay(3000);
				diagonalTest();
				break;
			case curve:
				pros::delay(3000);
				curveTest();
				break;
			default:
				break;
		}

		if (Test != none) Test = none;

		pros::delay(10);
	}
}

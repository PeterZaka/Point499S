#include "main.h"
#include "auto/autonomous.hpp"

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

	iSensor.reset();
	pros::delay(20);
	while(iSensor.is_calibrating()){
		printf("calibrating...\n");
		pros::delay(200);
	}
	printf("done calibrating\n");
}


void disabled() {}


void competition_initialize() {}


void autonomous() {

	pros::Task calculateOdomTask([]()
		{
		while(1){
			calculateOdom();
			pros::delay(10);
		}
		});

		pros::Task debugTask([]()
		{
			while(1){
				printf("Pos: (%.2lf, %.2lf, %.2lf)\n", xPos, yPos, rot);
				printf("Encoder: (%.2lf, %.2lf, %.2lf)\n\n", leftEncoder.get(), backEncoder.get(), rightEncoder.get());
				pros::delay(1000);
			}
		});

		autonFunc();
}

void opcontrol() {

	clawBack.setBrakeMode(AbstractMotor::brakeMode::hold);

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
	// 		if (isDebugging) {
	// 			printf("\n");
	// 			std::cout << "x: " << xPos << std::endl;
	// 			std::cout << "y: " << yPos << std::endl;
	// 			std::cout << "rot: " << rot << std::endl;
	// 		}
	// 		pros::delay(5000 * 1);
	// 	}
	// 	});

	// pros::Task adebugTask([]()
	// {
	// 	while(1){
	// 		printf("Pos: (%.2lf, %.2lf, %.2lf)\n", xPos, yPos, rot);
	// 		printf("Encoder: (%.2lf, %.2lf, %.2lf)\n\n", leftEncoder.get(), backEncoder.get(), rightEncoder.get());
	// 		pros::delay(1000);
	// 	}
	// });

	// pros::Task debugTask([]()
	// {
	// 	ControllerButton printPosButton(ControllerDigital::A);
	// 	ControllerButton resetPosButton(ControllerDigital::Y);
	// 	while(1){
	// 		if (resetPosButton.changedToPressed()) {
	// 			isDebugging = true;
	// 			xPos = 0;
	// 			yPos = 0;
	// 			iSensor.tare();
	// 		}
	// 		if (isDebugging){
	// 			update_debug_page();
	// 			if (printPosButton.changedToPressed()){
	// 				printf("Pos: (%.2lf, %.2lf, %.2lf)\n", xPos, yPos, rot);
	// 				printf("Encoder: (%.2lf, %.2lf, %.2lf)\n\n", leftEncoder.get(), backEncoder.get(), rightEncoder.get());
	// 			}
	// 		}
	// 		pros::delay(50);
	// 	}
	// });


	// Master controller by default
	Controller controller(ControllerId::master);
	Controller controllerPartner(ControllerId::partner);

	pros::Task temperatureTask([&](){
		while(1){
			controller.clear();
			pros::delay(50);
			controller.setText(0, 0, "Left Lift: " + std::to_string((int)leftLift.getTemperature()));
			pros::delay(50);
			controller.setText(1, 0, "Right Lift: " + std::to_string((int)rightLift.getTemperature()));
			pros::delay(500);
		}
	});

	ControllerButton liftUpButton(ControllerId::master, ControllerDigital::R1);
	ControllerButton liftDownButton(ControllerId::master, ControllerDigital::R2);
	ControllerButton testButton(ControllerId::master, ControllerDigital::A);
	ControllerButton setForwardButton(ControllerId::master, ControllerDigital::up);
	ControllerButton setBackwardButton(ControllerId::master, ControllerDigital::down);

	ControllerButton clawFrontUpButton(ControllerId::partner, ControllerDigital::R1);
	ControllerButton clawFrontDownButton(ControllerId::partner, ControllerDigital::R2);
	ControllerButton clawBackUpButton(ControllerId::partner, ControllerDigital::L1);
	ControllerButton clawBackDownButton(ControllerId::partner, ControllerDigital::L2);
	ControllerButton clawRegularButton(ControllerId::partner, ControllerDigital::up);
	ControllerButton clawSlowButton(ControllerId::partner, ControllerDigital::down);

	bool isTank = true;
	bool isBackward = false;

	double clawSpeed = 1;

	// xPos = 8.5;
	// yPos = 8.5;

	xPos = 29.5;
	yPos = 15.5;

	while (true) {
		double leftYAxis = controller.getAnalog(ControllerAnalog::leftY);
		double rightYAxis = controller.getAnalog(ControllerAnalog::rightY);
		double rightXAxis = controller.getAnalog(ControllerAnalog::rightX);
		if (isTank) {
			if(abs(leftYAxis) < 0.1) leftYAxis = -controllerPartner.getAnalog(ControllerAnalog::rightY);
			if(abs(rightYAxis) < 0.1) rightYAxis = -controllerPartner.getAnalog(ControllerAnalog::leftY);
		} else {
			if(abs(leftYAxis) < 0.1) leftYAxis = -controllerPartner.getAnalog(ControllerAnalog::leftY);
			if(abs(rightXAxis) < 0.1) rightXAxis = -controllerPartner.getAnalog(ControllerAnalog::rightX);
		}
		if(abs(leftYAxis) < 0.1) leftYAxis = 0;
		if(abs(rightYAxis) < 0.1) rightYAxis = 0;
		if(abs(rightXAxis) < 0.1) rightXAxis = 0;

		if (setForwardButton.changedToPressed()) {
			controller.rumble("..");
			isBackward = false;
		}
		if (setBackwardButton.changedToPressed()) {
			controller.rumble("-");
			isBackward = true;
		}

		if (clawRegularButton.changedToPressed()) {
			controllerPartner.rumble("..");
			clawSpeed = 1;
		}
		if (clawSlowButton.changedToPressed()) {
			controllerPartner.rumble("-");
			clawSpeed = 0.5;
		}

		if (isTank) {
			if (isBackward) {
				double tempRightYAxis = rightYAxis;
				rightYAxis = -leftYAxis;
				leftYAxis = -tempRightYAxis;
			}
			leftSide.moveVoltage((leftYAxis) * 12000.0);
			rightSide.moveVoltage((rightYAxis) * 12000.0);
		} else {
			leftSide.moveVoltage((leftYAxis + rightXAxis) * 12000.0);
			rightSide.moveVoltage((leftYAxis - rightXAxis) * 12000.0);
		}

		if (isTank) {
			leftSide.moveVoltage((leftYAxis) * 12000.0);
			rightSide.moveVoltage((rightYAxis) * 12000.0);
		} else {
			leftSide.moveVoltage((leftYAxis + rightXAxis) * 12000.0);
			rightSide.moveVoltage((leftYAxis - rightXAxis) * 12000.0);
		}

		if(liftUpButton.isPressed()) lift.moveVoltage(12000.0 * liftPower);
		else if(liftDownButton.isPressed()) lift.moveVoltage(-12000.0 * liftPower);
		else lift.moveVoltage(0.0);

		if(clawFrontUpButton.isPressed()) clawFront.moveVoltage(12000.0 * clawSpeed);
		else if(clawFrontDownButton.isPressed()) clawFront.moveVoltage(-12000.0 * clawSpeed);
		else clawFront.moveVoltage(0);

		if(clawBackUpButton.isPressed()) clawBack.moveVoltage(12000.0 * clawSpeed);
		else if(clawBackDownButton.isPressed()) clawBack.moveVoltage(-12000.0 * clawSpeed);
		else clawBack.moveVoltage(0);

		if (testButton.isPressed()) autonFunc();

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

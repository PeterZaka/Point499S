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
}


void disabled() {}


void competition_initialize() {}


void autonomous() {
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

	groupMoveTo(clawFront, -1400, 24);
	driveToPoint(0, 63, best);
	turnToAngle(-15);
	groupMoveTo(clawFront, 1200);
	driveToPoint(0, 0, best);
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
	// 		if (isDebugging) {
	// 			printf("\n");
	// 			std::cout << "x: " << xPos << std::endl;
	// 			std::cout << "y: " << yPos << std::endl;
	// 			std::cout << "rot: " << rot << std::endl;
	// 		}
	// 		pros::delay(5000 * 1);
	// 	}
	// 	});

	pros::Task debugTask([]()
	{
		ControllerButton printPosButton(ControllerDigital::A);
		ControllerButton resetPosButton(ControllerDigital::Y);
		while(1){
			if (resetPosButton.changedToPressed()) {
				isDebugging = true;
				xPos = 0;
				yPos = 0;
				iSensor.tare();
			}
			if (isDebugging){
				update_debug_page();
				if (printPosButton.changedToPressed()){
					printf("Pos: (%.2lf, %.2lf, %.2lf)\n", xPos, yPos, rot);
					printf("Encoder: (%.2lf, %.2lf, %.2lf)\n\n", leftEncoder.get(), backEncoder.get(), rightEncoder.get());
				}
			}
			pros::delay(50);
		}
	});

	// Master controller by default
	Controller controller(ControllerId::master);
	Controller controllerPartner(ControllerId::partner);

	ControllerButton liftUpButton(ControllerId::master, ControllerDigital::R1);
	ControllerButton liftDownButton(ControllerId::master, ControllerDigital::R2);
	ControllerButton clawFrontUpButton(ControllerId::partner, ControllerDigital::R1);
	ControllerButton clawFrontDownButton(ControllerId::partner, ControllerDigital::R2);
	ControllerButton clawBackUpButton(ControllerId::partner, ControllerDigital::L1);
	ControllerButton clawBackDownButton(ControllerId::partner, ControllerDigital::L2);

	bool isDrivingStraight = false;
	bool isLiftStopped = false;
	bool isTank = true;

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

		bool isStraightArcade = (!isTank && abs(rightXAxis) < 0.1 && abs(leftYAxis) > 0);
		bool isStraightTank = (abs(leftYAxis) > 0 && abs(rightYAxis) > 0 && // if moving jotsticks
		 (abs(leftYAxis - rightYAxis) < 0.1));
		if(isStraightArcade || isStraightTank){ // if joysticks in simillar range
			if(isDrivingStraight == false){
				isDrivingStraight = true;
				anglePID.setTarget(rot);
			} else {
				anglePID.update(rot);
			}
		} else {
			isDrivingStraight = false;
		}

		//isDrivingStraight = false;

		if(isDrivingStraight){
			if (isTank) {
				leftSide.moveVoltage((leftYAxis + anglePID.value() / 100.0) * 12000.0);
				rightSide.moveVoltage((rightYAxis - anglePID.value() / 100.0) * 12000.0);
			} else {
				leftSide.moveVoltage((leftYAxis + rightXAxis + anglePID.value() / 100.0) * 12000.0);
				rightSide.moveVoltage((leftYAxis - rightXAxis - anglePID.value() / 100.0) * 12000.0);
			}
		} else {
			if (isTank) {
				leftSide.moveVoltage((leftYAxis) * 12000.0);
				rightSide.moveVoltage((rightYAxis) * 12000.0);
			} else {
				leftSide.moveVoltage((leftYAxis + rightXAxis) * 12000.0);
				rightSide.moveVoltage((leftYAxis - rightXAxis) * 12000.0);
			}
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

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
	iSensor.reset();

	vision.set_signature(1, &SIG_YELLOW);
	vision.set_signature(2, &SIG_RED);

	autonSelectScreenInitialize();

	clawBack.setBrakeMode(AbstractMotor::brakeMode::hold);

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

	pros::Task calculateOdomTask([](){
		while(1){
			calculateOdom();
			pros::delay(10);
		}
	});

		// pros::Task debugTask([]()
		// {
		// 	while(1){
		// 		printf("Pos: (%.2lf, %.2lf, %.2lf)\n", xPos, yPos, rot);
		// 		printf("Encoder: (%.2lf, %.2lf, %.2lf)\n\n", leftEncoder.get(), backEncoder.get(), rightEncoder.get());
		// 		pros::delay(1000);
		// 	}
		// });

		autonFunc();
}

void opcontrol() {

	pros::Task calculateOdomTask([](){
		while(1){
			calculateOdom();
			pros::delay(10);
		}
	});

	// pros::Task debugTask([]()
	// {
	// 	while(1){
	// 		printf("Pos: (%.2lf, %.2lf, %.2lf)\n", xPos, yPos, rot);
	// 		printf("Encoder: (%.2lf, %.2lf, %.2lf)\n\n", leftEncoder.get(), backEncoder.get(), rightEncoder.get());
	// 		pros::delay(1000);
	// 	}
	// });

	// Master controller by default
	Controller controller(ControllerId::master);
	Controller controllerPartner(ControllerId::partner);

	bool isLiftBoostEnabled = false;

	pros::Task controllerPrintTask([&](){
		while(1){
			controller.clear();

			// pros::delay(50);
			// controller.setText(0, 0, "Left Lift: " + std::to_string(leftLift.getTemperature()));
			// pros::delay(50);
			// controller.setText(1, 0, "Right Lift: " + std::to_string(rightLift.getTemperature()));
			// pros::delay(50);
			// controller.setText(2, 0, "Boost Enabled: " + std::to_string(isLiftBoostEnabled));

			pros::delay(50);
			controller.setText(0, 0, "x: " + std::to_string(xPos));
			pros::delay(50);
			controller.setText(1, 0, "y: " + std::to_string(yPos));
			pros::delay(50);
			controller.setText(2, 0, "rot: " + std::to_string(rot));

			// pros::delay(50);
			// controller.setText(0, 0, "l: " + std::to_string(leftEncoder.get()));
			// pros::delay(50);
			// controller.setText(1, 0, "r: " + std::to_string(rightEncoder.get()));
			// pros::delay(50);
			// controller.setText(2, 0, "rot: " + std::to_string(calculatedRot * (180/pi)));

			pros::delay(500);
		}
	});

	// ------- Main -------
	ControllerButton liftUpButton(ControllerId::master, ControllerDigital::R1);
	ControllerButton liftDownButton(ControllerId::master, ControllerDigital::R2);
	ControllerButton setForwardButton(ControllerId::master, ControllerDigital::up);
	ControllerButton setBackwardButton(ControllerId::master, ControllerDigital::down);
	ControllerButton enableBoostButton(ControllerId::master, ControllerDigital::L1);
	ControllerButton disableBoostButton(ControllerId::master, ControllerDigital::L2);
	ControllerButton testButton(ControllerId::master, ControllerDigital::A);
	ControllerButton debugButton(ControllerId::master, ControllerDigital::Y);
	// 1 controller only
	ControllerButton singleClawFrontUpButton(ControllerId::master, ControllerDigital::right);
	ControllerButton singleClawFrontDownButton(ControllerId::master, ControllerDigital::left);
	ControllerButton singleClawBackUpButton(ControllerId::master, ControllerDigital::X);
	ControllerButton singleClawBackDownButton(ControllerId::master, ControllerDigital::B);

	// ------- Partner -------
	ControllerButton clawFrontUpButton(ControllerId::partner, ControllerDigital::R1);
	ControllerButton clawFrontDownButton(ControllerId::partner, ControllerDigital::R2);
	ControllerButton clawBackUpButton(ControllerId::partner, ControllerDigital::L1);
	ControllerButton clawBackDownButton(ControllerId::partner, ControllerDigital::L2);
	ControllerButton clawRegularButton(ControllerId::partner, ControllerDigital::up);
	ControllerButton clawSlowButton(ControllerId::partner, ControllerDigital::down);

	bool isTank = true;
	bool isBackward = false;

	double clawSpeed = 1;

	xPos = 24+14.5/2;
	yPos = 17.25/2;

	StartDebugTime("Y Pressed: ");
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
		} else if (setBackwardButton.changedToPressed()) {
			controller.rumble("-");
			isBackward = true;
		}
		if (enableBoostButton.changedToPressed()) {
			controller.rumble(".");
			isLiftBoostEnabled = true;
		} else if (disableBoostButton.changedToPressed()) {
			controller.rumble(".");
			isLiftBoostEnabled = false;
		}

		if (clawRegularButton.changedToPressed()) {
			controllerPartner.rumble("..");
			clawSpeed = 1;
		} else if (clawSlowButton.changedToPressed()) {
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

		if(liftUpButton.isPressed()){
			liftBoost.set_value(true);
			lift.moveVoltage(12000.0);
		} else if(liftDownButton.isPressed()){
			liftBoost.set_value(false);
			lift.moveVoltage(-12000.0);
		} else {
			liftBoost.set_value(false);
			lift.moveVoltage(0.0);
		}

		if (controllerPartner.isConnected()) {
			if(clawFrontUpButton.isPressed()) clawFront.set_value(false);
			else if(clawFrontDownButton.isPressed()) clawFront.set_value(true);

			if(clawBackUpButton.isPressed()) clawBack.moveVoltage(12000.0 * clawSpeed);
			else if(clawBackDownButton.isPressed()) clawBack.moveVoltage(-12000.0 * clawSpeed);
			else clawBack.moveVoltage(0);
		}
		else {
			if(singleClawFrontUpButton.isPressed()) clawFront.set_value(false);
			else if(singleClawFrontDownButton.isPressed()) clawFront.set_value(true);

			if(singleClawBackUpButton.isPressed()) clawBack.moveVoltage(12000.0);
			else if(singleClawBackDownButton.isPressed()) clawBack.moveVoltage(-12000.0);
			else clawBack.moveVoltage(0);
		}

		if (debugButton.changedToPressed()) {
			printf("\n");
			PrintDebugTime("Y Pressed: ");
			PrintPosition();
		}

		if (testButton.changedToPressed()) {
			controller.rumble(".");
			StartDebugTime("Y Pressed: ");
			pros::Task testingTask(autonFunc);
			std::cout << testingTask.get_state() << std::endl;
			while (testingTask.get_state() == pros::E_TASK_STATE_READY){
				if (clawFrontButton.changedToPressed()) controller.rumble("..");
				if (clawBackButton.changedToPressed()) controller.rumble("..");
				if (debugButton.changedToPressed()) {
					printf("\n");
					PrintDebugTime("Y Pressed: ");
					PrintPosition();
				}
				if (testButton.changedToPressed()) testingTask.remove();
				pros::delay(20);
			}
			std::cout << testingTask.get_state() << std::endl;
			controller.rumble(".");
		}

		pros::delay(10);
	}
}

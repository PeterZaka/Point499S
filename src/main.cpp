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

	pros::delay(20);
	printf("calibrating...\n");
	while(iSensor.is_calibrating()){
		pros::delay(50);
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

	// Master controller by default
	Controller controller(ControllerId::master);
	Controller controllerPartner(ControllerId::partner);

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
			// controller.setText(2, 0, "b: " + std::to_string(backEncoder.get()));
			// controller.setText(2, 0, "rot: " + std::to_string(calculatedRot * (180/pi)));

			// pros::delay(50);
			// controller.setText(0, 0, "r - p: " + std::to_string(rot - prevRot));
			// pros::delay(50);
			// controller.setText(1, 0, "c: " + std::to_string((deltaL - deltaR) / wheelTrack));
			// pros::delay(50);
			// controller.setText(2, 0, "liftP: " + std::to_string(liftPot.get()));

			pros::delay(500);
		}
	});

	// ------- Main -------
	ControllerButton liftUpButton(ControllerId::master, ControllerDigital::R1);
	ControllerButton liftDownButton(ControllerId::master, ControllerDigital::R2);
	ControllerButton setForwardButton(ControllerId::master, ControllerDigital::up);
	ControllerButton setBackwardButton(ControllerId::master, ControllerDigital::down);
	ControllerButton testButton(ControllerId::master, ControllerDigital::A);
	ControllerButton debugButton(ControllerId::master, ControllerDigital::Y);
	// 1 controller only
	ControllerButton singleClawFrontOpenButton(ControllerId::master, ControllerDigital::right);
	ControllerButton singleClawFrontCloseButton(ControllerId::master, ControllerDigital::left);
	ControllerButton singleClawBackOpenButton(ControllerId::master, ControllerDigital::X);
	ControllerButton singleClawBackCloseButton(ControllerId::master, ControllerDigital::B);
	ControllerButton singleBackArmUpButton(ControllerId::partner, ControllerDigital::L1);
	ControllerButton singleBackArmDownButton(ControllerId::partner, ControllerDigital::L2);

	// ------- Partner -------
	ControllerButton clawFrontOpenButton(ControllerId::partner, ControllerDigital::R1);
	ControllerButton clawFrontCloseButton(ControllerId::partner, ControllerDigital::R2);
	ControllerButton clawBackOpenButton(ControllerId::partner, ControllerDigital::L1);
	ControllerButton clawBackCloseButton(ControllerId::partner, ControllerDigital::L2);
	ControllerButton backArmUpButton(ControllerId::partner, ControllerDigital::X);
	ControllerButton backArmDownButton(ControllerId::partner, ControllerDigital::B);

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
			lift.moveVoltage(12000.0);
		} else if(liftDownButton.isPressed()){
			lift.moveVoltage(-12000.0);
		} else {
			lift.moveVoltage(0.0);
		}

		if (controllerPartner.isConnected()) {
			if(clawFrontOpenButton.isPressed()) clawFront.set_value(false);
			else if(clawFrontCloseButton.isPressed()) clawFront.set_value(true);

			if(clawBackOpenButton.isPressed()) clawBack.set_value(false);
			else if(clawBackCloseButton.isPressed()) clawBack.set_value(true);

			if(backArmUpButton.isPressed()) backArm.moveVoltage(12000.0);
			else if(backArmDownButton.isPressed()) backArm.moveVoltage(-12000.0);
			else backArm.moveVoltage(0);
		}
		else {
			if(singleClawFrontOpenButton.isPressed()) clawFront.set_value(false);
			else if(singleClawFrontCloseButton.isPressed()) clawFront.set_value(true);

			if(singleClawBackOpenButton.isPressed()) clawBack.set_value(false);
			else if(singleClawBackCloseButton.isPressed()) clawBack.set_value(true);

			if(singleBackArmUpButton.isPressed()) backArm.moveVoltage(12000.0);
			else if(singleBackArmDownButton.isPressed()) backArm.moveVoltage(-12000.0);
			else backArm.moveVoltage(0);
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
			controller.rumble(".");
		}

		pros::delay(10);
	}
}

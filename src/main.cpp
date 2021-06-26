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
	claw.setBrakeMode(AbstractMotor::brakeMode::hold);

	autonSelectScreenInitialize();
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

	pros::Task printTask([]()
		{
		while(1){
			printf("\n");
			printEncoders();
			printOdom();
			pros::delay(3000);
		}
		});

	// Master controller by default
	Controller controller;

	ControllerButton intakeUpButton(ControllerDigital::R2);
	ControllerButton intakeDownButton(ControllerDigital::R1);
	ControllerButton liftUpButton(ControllerDigital::L2);
	ControllerButton liftDownButton(ControllerDigital::L1);
	ControllerButton clawOpenButton(ControllerDigital::A);
	ControllerButton clawCloseButton(ControllerDigital::B);

	ControllerButton test1Button(ControllerDigital::up);
	ControllerButton test2Button(ControllerDigital::right);
	ControllerButton test3Button(ControllerDigital::left);
	// ControllerButton test4Button(ControllerDigital::Y);
	ControllerButton balanceButton(ControllerDigital::down);

	bool isDrivingStraight = false;

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

		if(isDrivingStraight){
			leftSide.moveVoltage((leftYAxis + anglePID.value() / 100.0) * 12000.0);
			rightSide.moveVoltage((leftYAxis - anglePID.value() / 100.0) * 12000.0);
		} else {
			leftSide.moveVoltage((leftYAxis) * 12000.0);
			rightSide.moveVoltage((rightYAxis) * 12000.0);
		}

		if(intakeUpButton.isPressed()) intake.moveVoltage(12000.0);
		else if(intakeDownButton.isPressed()) intake.moveVoltage(-12000.0);
		else intake.moveVoltage(0);

		if(liftUpButton.isPressed()) lift.moveVoltage(12000.0);
		else if(liftDownButton.isPressed()) lift.moveVoltage(-12000.0);
		else lift.moveVoltage(0);

		if(clawOpenButton.isPressed()) claw.moveVoltage(12000.0);
		else if(clawCloseButton.isPressed()) claw.moveVoltage(-12000.0);
		else claw.moveVoltage(0);

		if (test1Button.changedToPressed()) test1();
		else if (test2Button.changedToPressed()) test2();
		else if (test3Button.changedToPressed()) test3();
		else if (balanceButton.changedToPressed()) balance({3, 0, 0});
		// else if (test4Button.changedToPressed()) test4();

		pros::delay(10);
	}
}

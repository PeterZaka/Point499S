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

	clawForward.setBrakeMode(AbstractMotor::brakeMode::hold);
	clawBackward.setBrakeMode(AbstractMotor::brakeMode::hold);
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
	ControllerButton clawForwardUpButton(ControllerDigital::L1);
	ControllerButton clawForwardDownButton(ControllerDigital::L2);
	ControllerButton clawBackwardUpButton(ControllerDigital::X);
	ControllerButton clawBackwardDownButton(ControllerDigital::B);

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

		if(clawForwardUpButton.isPressed()) clawForward.moveVoltage(12000.0 * 0.9);
		else if(clawForwardDownButton.isPressed()) clawForward.moveVoltage(-12000.0 * 0.9);
		else clawForward.moveVoltage(0);

		if(clawBackwardUpButton.isPressed()) clawBackward.moveVoltage(12000.0 * 0.9);
		else if(clawBackwardDownButton.isPressed()) clawBackward.moveVoltage(-12000.0 * 0.9);
		else clawBackward.moveVoltage(0);

		pros::delay(10);
	}
}

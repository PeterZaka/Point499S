#pragma once

#include "okapi/api.hpp"
#include "auto/pid.hpp"

using namespace okapi;

extern Motor topLeftMotor;
extern Motor topRightMotor;
extern Motor backLeftMotor;
extern Motor backRightMotor;
extern MotorGroup leftSide;
extern MotorGroup rightSide;

extern pros::ADIDigitalOut clawFront;
extern MotorGroup clawBack;
extern MotorGroup leftLift;
extern MotorGroup rightLift;
extern MotorGroup lift;
extern pros::ADIDigitalOut liftBoost;

extern ADIEncoder leftEncoder;
extern ADIEncoder rightEncoder;
extern ADIEncoder backEncoder;

extern ADIButton clawFrontButton;
extern ADIButton clawBackButton;

extern pros::Imu iSensor;

extern pros::Vision vision;
extern pros::vision_signature SIG_YELLOW;
extern pros::vision_signature SIG_RED;

extern PID drivePID;
extern PID anglePID;
extern PID turnPID;
extern PID colorPID;

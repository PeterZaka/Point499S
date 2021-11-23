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

extern MotorGroup clawFront;
extern MotorGroup clawBack;
extern MotorGroup leftLift;
extern MotorGroup rightLift;
extern MotorGroup lift;
extern PID rightLiftPID;
extern PID liftPID;

extern ADIEncoder leftEncoder;
extern ADIEncoder rightEncoder;
extern ADIEncoder backEncoder;
extern ADIButton clawFrontButton;
extern ADIButton clawBackButton;

extern pros::Imu iSensor;

extern PID drivePID;
extern PID anglePID;
extern PID turnPID;

#pragma once

#include "okapi/api.hpp"
using namespace okapi;

extern Motor topLeftMotor;
extern Motor topRightMotor;
extern Motor backLeftMotor;
extern Motor backRightMotor;
extern MotorGroup leftSide;
extern MotorGroup rightSide;

extern std::shared_ptr<OdomChassisController> chassis;

extern std::shared_ptr<XDriveModel> drive;

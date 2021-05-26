#pragma once

#include "main.h"

extern Motor topLeftMotor;
extern Motor topRightMotor;
extern Motor backLeftMotor;
extern Motor backRightMotor;

extern std::shared_ptr<OdomChassisController> chassis;

extern std::shared_ptr<XDriveModel> drive;

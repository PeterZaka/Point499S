#pragma once

#include "okapi/api.hpp"
#include "auto/pid.hpp"

using namespace okapi;

extern ADIEncoder leftEncoder;
extern ADIEncoder rightEncoder;
extern ADIEncoder backEncoder;

extern pros::Imu iSensor;

extern PID drivePID;
extern PID anglePID;
extern PID turnPID;

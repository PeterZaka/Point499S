#include "chassis.hpp"

Motor topLeftMotor(-3);
Motor topRightMotor(4);
Motor backLeftMotor(-1);
Motor backRightMotor(2);
MotorGroup leftSide({topLeftMotor});
MotorGroup rightSide({topRightMotor});

#include "chassis.hpp"

Motor topLeftMotor(2);
Motor topRightMotor(-1);
Motor backLeftMotor(4);
Motor backRightMotor(-3);
MotorGroup leftSide({topLeftMotor, backLeftMotor});
MotorGroup rightSide({topRightMotor, backRightMotor});

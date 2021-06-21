#include "chassis.hpp"

Motor topLeftMotor(10);
Motor topRightMotor(-19);
Motor backLeftMotor(9);
Motor backRightMotor(-20);
MotorGroup leftSide({topLeftMotor, backLeftMotor});
MotorGroup rightSide({topRightMotor, backRightMotor});

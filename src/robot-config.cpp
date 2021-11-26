#include "robot-config.hpp"

Motor topLeftMotor(-2);
Motor topRightMotor(1);
Motor backLeftMotor(-4);
Motor backRightMotor(3);
MotorGroup leftSide({topLeftMotor, backLeftMotor});
MotorGroup rightSide({topRightMotor, backRightMotor});

pros::ADIDigitalOut clawFront({1, 'A'}, false);
MotorGroup clawBack({-17});
MotorGroup leftLift({-8});
MotorGroup rightLift({10});
MotorGroup lift({-8, 10});

pros::ADIDigitalOut liftBoost({1, 'B'}, false);

ADIEncoder leftEncoder('G', 'H');
ADIEncoder rightEncoder('E', 'F', true);
ADIEncoder backEncoder('A', 'B');

ADIButton clawFrontButton('D');
ADIButton clawBackButton('C');

pros::Imu iSensor(7);

pros::Vision vision(9);
pros::vision_signature SIG_YELLOW = pros::Vision::signature_from_utility(1, 0, 0, 0, 0, 0, 0, 2.500, 0);

PID drivePID(10, 0, 0);
PID anglePID(2, 0, 0);
PID turnPID(1.7, 0.2, 0, 10, 1);
PID colorPID(1, 0, 0);

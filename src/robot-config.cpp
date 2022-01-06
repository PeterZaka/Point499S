#include "robot-config.hpp"

Motor topLeftMotor(-2);
Motor topRightMotor(1);
Motor backLeftMotor(-4);
Motor backRightMotor(3);
MotorGroup leftSide({topLeftMotor, backLeftMotor});
MotorGroup rightSide({topRightMotor, backRightMotor});

Motor leftLift(-8);
Motor rightLift(10);
MotorGroup lift({leftLift, rightLift});

MotorGroup backArm({12});

pros::ADIDigitalOut clawFront({1, 'A'}, false);
pros::ADIDigitalOut clawBack({1, 'B'}, false);

ADIEncoder leftEncoder('E', 'F', true);
ADIEncoder rightEncoder('G', 'H');
ADIEncoder backEncoder('A', 'B');

Potentiometer liftPot({1, 'C'});

ADIButton clawFrontButton('D');
ADIButton clawBackButton('C');

pros::Imu iSensor(7);

pros::Vision vision(13);
pros::vision_signature SIG_YELLOW = pros::Vision::signature_from_utility(1, 1579, 2173, 1876, -3589, -3319, -3454, 3.000, 0);
pros::vision_signature SIG_RED = pros::Vision::signature_from_utility(2, 4207, 5017, 4612, -411, 1, -204, 4.800, 0);

PID drivePID(10, 0, 0);
PID anglePID(2, 0, 0);
PID turnPID(1.7, 0.2, 0, 10, 1);
PID colorPID(0.5, 0, 0);

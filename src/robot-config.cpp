#include "robot-config.hpp"

Motor topLeftMotor(-2);
Motor topRightMotor(1);
Motor backLeftMotor(-4);
Motor backRightMotor(3);
MotorGroup leftSide({topLeftMotor, backLeftMotor});
MotorGroup rightSide({topRightMotor, backRightMotor});

Motor leftLift(8);
Motor rightLift(-9);
MotorGroup lift({leftLift, rightLift});

MotorGroup frontArm({-10});
MotorGroup backArm({-18});
// actually 18

pros::ADIDigitalOut clawFront({15, 'B'}, false);
pros::ADIDigitalOut clawBack({15, 'A'}, false);

ADIEncoder leftEncoder('E', 'F', true);
ADIEncoder rightEncoder('G', 'H');
ADIEncoder backEncoder('A', 'B');

Potentiometer backArmPot({15, 'F'});

ADIButton clawFrontLeftButton('C');
ADIButton clawFrontRightButton({15, 'G'}, false);
ADIButton clawBackLeftButton('D');
ADIButton clawBackRightButton('D');
pros::Imu iSensor(7);

pros::Vision vision(19);
pros::vision_signature SIG_YELLOW = pros::Vision::signature_from_utility(1, 1579, 2173, 1876, -3589, -3319, -3454, 3.000, 0);
pros::vision_signature SIG_RED = pros::Vision::signature_from_utility(2, 4207, 5017, 4612, -411, 1, -204, 4.800, 0);

PID drivePID(10, 0, 0);
PID anglePID(2, 0, 0);
PID turnPID(1.7, 0.2, 0, 10, 1);
PID colorPID(0.5, 0, 0);

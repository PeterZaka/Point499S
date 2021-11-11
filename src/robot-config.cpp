#include "robot-config.hpp"

MotorGroup clawFront({-13});
MotorGroup clawBack({-16});
MotorGroup leftLift({-8});
MotorGroup rightLift({10});
MotorGroup lift({-8, 10});
PID rightLiftPID(0, 0, 0);
PID liftPID(1, 0, 0);

ADIEncoder leftEncoder('G', 'H');
ADIEncoder rightEncoder('E', 'F', true);
ADIEncoder backEncoder('A', 'B');
Potentiometer clawFrontPot(10);
ADIButton clawFrontButton('D');
ADIButton clawBackButton('C');

pros::Imu iSensor(7);

PID drivePID(10, 0, 0);
PID anglePID(2, 0, 0);
PID turnPID(1.7, 0.2, 0, 10, 1);

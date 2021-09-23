#include "robot-config.hpp"

MotorGroup clawFront({-13});
MotorGroup clawBack({-11});
MotorGroup leftLift({-6});
MotorGroup rightLift({9});
MotorGroup lift({-6, 9});
PID rightLiftPID(0, 0, 0);
PID liftPID(1, 0, 0);

ADIEncoder leftEncoder('G', 'H');
ADIEncoder rightEncoder('E', 'F', true);
ADIEncoder backEncoder('A', 'B');
Potentiometer clawFrontPot(10);

pros::Imu iSensor(5);

PID drivePID(8, 0, 0);
PID anglePID(2, 0, 0);
PID turnPID(1.7, 0.4, 0, 10, 2);

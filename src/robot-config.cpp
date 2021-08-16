#include "robot-config.hpp"

Motor claw(-11);
Motor leftLift(-6);
Motor rightLift(9);
MotorGroup lift({leftLift, rightLift});

ADIEncoder leftEncoder('E', 'F', true);
ADIEncoder rightEncoder('G', 'H');
ADIEncoder backEncoder('A', 'B');

pros::Imu iSensor(5);

PID drivePID(12, 0, 5);
PID anglePID(10, 0, 0);
PID turnPID(2, 0.1, 0, 10, 0.5);

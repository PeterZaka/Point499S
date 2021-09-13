#include "robot-config.hpp"

Motor clawFront(-13);
Motor clawBack(-11);
Motor leftLift(-6);
Motor rightLift(9);
MotorGroup lift({leftLift, rightLift});
PID rightLiftPID(0, 0, 0);
PID liftPID(1, 0, 0);

ADIEncoder leftEncoder('G', 'H');
ADIEncoder rightEncoder('E', 'F', true);
ADIEncoder backEncoder('A', 'B');

pros::Imu iSensor(5);

// 12 0 5
PID drivePID(8, 0, 0);
PID anglePID(2, 0, 0);
// 2, 0.1, 0, 10, 0.5
PID turnPID(1.6, 0.2, 0, 10, 0.5);

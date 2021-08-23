#include "robot-config.hpp"

Motor claw(-11);
Motor leftLift(-6);
Motor rightLift(10);
MotorGroup lift({leftLift, rightLift});
PID rightLiftPID(0, 0, 0);
PID liftPID(1, 0, 0);

ADIEncoder leftEncoder('E', 'F');
ADIEncoder rightEncoder('G', 'H', true);
ADIEncoder backEncoder('A', 'B', true);

pros::Imu iSensor(5);

// 12 0 5
PID drivePID(12, 0, 0);
PID anglePID(10, 0, 0);
// 2, 0.1, 0, 10, 0.5
PID turnPID(1.75, 0.2, 0, 10, 0.5);

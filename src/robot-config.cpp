#include "robot-config.hpp"

Motor intake(7);

ADIEncoder leftEncoder('E', 'F', true);
ADIEncoder rightEncoder('G', 'H');
ADIEncoder backEncoder('A', 'B');

pros::Imu iSensor(5);

PID drivePID(15, 0, 5);
PID anglePID(10, 0, 0);
PID turnPID(3, 0.3, 0, 15, 0.5);

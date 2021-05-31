#include "robot-config.hpp"

ADIEncoder leftEncoder('E', 'F', true);
ADIEncoder rightEncoder('G', 'H');
ADIEncoder backEncoder('A', 'B');

pros::Imu iSensor(17);

PID drivePID(20, 0, 5);
PID anglePID(5, 0, 0);
PID turnPID(3, 0.3, 0, 15, 1);

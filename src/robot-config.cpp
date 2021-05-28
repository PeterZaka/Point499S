#include "robot-config.hpp"

ADIEncoder leftEncoder('E', 'F', true);
ADIEncoder rightEncoder('G', 'H');
ADIEncoder backEncoder('A', 'B');

IMU iSensor(17);

PID drivePID(2, 0, 0);
PID anglePID(2, 0, 0);
PID turnPID(3, 0, 0);

#include "robot-config.hpp"

ADIEncoder leftEncoder('E', 'F', true);
ADIEncoder rightEncoder('G', 'H');
ADIEncoder backEncoder('A', 'B');

IMU iSensor(17);

PID drivePID(20, 0, 5);
PID anglePID(5, 0, 0);
PID turnPID(3, 0, 0);

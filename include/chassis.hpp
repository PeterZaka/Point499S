#pragma once

#include "main.h"

extern ADIEncoder leftEncoder;
extern ADIEncoder rightEncoder;
extern ADIEncoder backEncoder;

extern std::shared_ptr<OdomChassisController> chassis;

extern std::shared_ptr<XDriveModel> drive;

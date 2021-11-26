#pragma once

#include "pros/apix.h"
#include "auto/odometry.hpp"

#include <string>
#include <map>

extern bool DebugDriveForward;
extern bool DebugDriveToPoint;
extern bool DebugTurn;
extern bool DebugGroupMoveTo;

void StartDebugTime(std::string tag="");

void PrintDebugTime(std::string tag="");

void PrintPosition(std::string tag="");

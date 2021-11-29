#include "debug.hpp"

bool DebugDriveForward = false;
bool DebugDriveToPoint = false;
bool DebugTurn = false;
bool DebugGroupMoveTo = false;

static std::map<std::string, double> tags;

void StartDebugTime(std::string tag) {
  tags[tag] = pros::millis() / 1000.0;
}

void PrintDebugTime(std::string tag) {
  std::cout << tag << (pros::millis() / 1000.0 - tags[tag]) << " seconds" << std::endl;
}

void PrintPosition(std::string tag) {
  printf("%s(%.2lf, %.2lf, %.2lf)\n", tag.c_str(), xPos, yPos, rot);
}

void Wait(double seconds){
  pros::delay(seconds * 1000);
}

#pragma once

#include <math.h>
#include <algorithm>

class PID{
  double Value;

public:

  double Kp;
  double Ki;
  double Kd;
  double integralLimit;
  double integralBound;
  double target;

  PID(double Kp, double Ki, double Kd, double integralLimit = 0, double integralBound = 0);

  double value() const { return Value; }

  void reset();

  void setTarget(double Target, bool shouldReset=true);

  void update(double current);

  double error;
  double integral;
  double derivative;
  double prevError;
};

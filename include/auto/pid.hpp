#pragma once

#include "main.h"

class PID{
  double Value;

public:

  double Kp;
  double Ki;
  double Kd;
  double integralLimit;
  double target;

  PID(double Kp, double Ki, double Kd, double integralLimit = 0);

  double value() const { return Value; }

  void reset();

  void setTarget(double Target);

  void update(double current);

  double error;
  double integral;
  double derivative;
  double prevError;
};

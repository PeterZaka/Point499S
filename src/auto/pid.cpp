#include "auto/pid.hpp"

PID::PID(double Kp, double Ki, double Kd, double integralLimit, double integralBound) :
Kp(Kp), Ki(Ki), Kd(Kd), integralLimit(integralLimit), integralBound(integralBound) {}

void PID::reset(){
  error = 0;
  integral = 0;
  derivative = 0;
  prevError = 0;
}

void PID::setTarget(double Target, bool shouldReset){
  if (shouldReset) reset();
  target = Target;
}

void PID::update(double current){
  error = target - current;

  if (Ki != 0) {
    if (abs(error) < integralLimit) {
      integral += error;
      integral = std::clamp(integral, -100000.0, 100000.0);
    }
    if (abs(error) < integralBound) {
      integral = 0;
    }
  }
  else {
    integral = 0;
  }

  derivative = prevError - error;
  prevError = error;

  Value = (error * Kp) + (integral * Ki) + (derivative * Kd);
  Value = std::clamp(Value, -100.0, 100.0);
}

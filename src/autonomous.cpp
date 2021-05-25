#include "autonomous.hpp"

void testingAuton(){
  chassis->setState({0_in, 0_in, 0_deg});

  chassis->turnToAngle(90_deg);

  chassis->turnToAngle(0_deg);
  
}

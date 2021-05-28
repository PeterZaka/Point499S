#include "auto/autonomous.hpp"

void fullTestAuton(){
  chassis->setState({0_in, 0_in, 0_deg});
  goTo(24, 24);
  goTo(0, 0);
  turnTo(0);
}

void turnTestAuton(){
  turnTo(90);

}

void driveTestAuton(){
  driveForward(24);

}

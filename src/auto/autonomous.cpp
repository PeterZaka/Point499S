#include "auto/autonomous.hpp"

void fullTestAuton(){
  chassis->setState({0_in, 0_in, 0_deg});

  chassis->driveToPoint({2_ft, 2_ft});

  chassis->driveToPoint({0_ft, 2_ft});

  chassis->turnToAngle(0_deg);

  chassis->driveToPoint({0_ft, 0_ft}, true);
}

void turnTestAuton(){
  chassis->setState({0_in, 0_in, 0_deg});

  chassis->turnToAngle(90_deg);

  chassis->turnToAngle(-90_deg);

  chassis->turnToAngle(0_deg);

}

void driveTestAuton(){
  chassis->setState({0_in, 0_in, 0_deg});

  chassis->driveToPoint({0_in, 4_ft});

  chassis->driveToPoint({0_in, 0_in}, true);
}

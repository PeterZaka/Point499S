#include "auto/autonomous.hpp"

#define t(x) [&]{x;}
#define r(x) [&]{return x;}

void testAuton(){
  // xPos = 24+14.5/2;
	// yPos = 17.25/2;
  //
  // driveToPoint(24, 24);
  // driveToPoint(3 *24, 4 *24, forward);

  xPos = 24;
  yPos = 24;

  iSensor.set_rotation(0);
  rot = 0;
  prevRot = 0;

  clawFront.set_value(true);
  Wait(1);
  clawFront.set_value(false);
  Wait(1);
  clawFront.set_value(true);
  Wait(1);
  clawFront.set_value(false);

}

void rightAuton(){

  xPos = 4.5 *24;
  yPos = 24 - 17.25/2.0;

  driveTargetTime = 0; // Don't stop

  doUntil(t(driveToPoint(4.5 *24, 3 *24, forward)), r(clawFrontButton.isPressed()));
  clawFront.set_value(true);

  driveStopError = 0; // Disable stop detection

  doUntil(t(driveToPoint(3 *24, 3 *24, backward)), r(clawBackButton.isPressed()));
  clawBack.set_value(true);

  driveToPoint((xPos+4 *24)/2.0, (yPos+1.5 *24)/2.0);
  pros::Task moveTowerToTop([]{
    backArm.moveVoltage(12000.0);
    Wait(3);
    clawBack.set_value(false);
    backArm.moveVoltage(-12000.0);
  });

  driveToPoint(4 *24, 1.5 *24);
  turnToPoint(5.5 *24, 1.5 *24, backward);
  doUntil(t(driveToPoint(5.5 *24, 1.5 *24, backward)), r(clawBackButton.isPressed()));
  clawBack.set_value(true);
}

void leftAuton(){

  xPos = 29.5;
	yPos = 24 - 17.25/2.0;

  driveTargetTime = 0; // Don't stop

  doUntil(t(driveToPoint(1.5 *24, 3 *24, forward)), r(clawFrontButton.isPressed()));
  clawFront.set_value(true);

  driveStopError = 0; // Disable stop detection

  doUntil(t(driveToPoint(3 *24, 3 *24, backward)), r(clawBackButton.isPressed()));
  clawBack.set_value(true);

  driveToPoint((xPos+1.5 *24)/2.0, (yPos+1.5 *24)/2.0);
  pros::Task moveTowerToTop([]{
    backArm.moveVoltage(12000.0);
    Wait(3);
    clawBack.set_value(false);
    backArm.moveVoltage(-12000.0);
  });

  driveToPoint(1.5 *24, 1.5 *24);
  driveToPoint(1 *24, 0.5 *24);

  turnToPoint(1.75 *24, 0.5 *24, backward);
  doUntil(t(driveToPoint(1.75 *24, 0.5 *24, backward)), r(clawBackButton.isPressed()));
  clawBack.set_value(true);
}

void skills(){

  xPos = 24+14.5/2.0;
	yPos = 17.25/2.0;

  iSensor.set_rotation(-90);
  rot = -90;
  prevRot = -90;

  driveTargetTime = 0;

  // --------------------- SLIDE 1 ---------------------
  // 1: Get left red
  // 2: Score left red
  // 3: Get middle neutral
  // 4: Score middle neutral

  // 1: Get left red
  driveForward(-12);
  clawBack.set_value(true);

  // 2: Score left red
  driveToPoint(1 *24, 1 *24);
  driveToPoint(2 *24, 2 *24, backward);
  driveToPoint(2.5 *24, 4 *24, backward);
  driveToPoint((2.5+3)/2.0 *24, (4+5)/2.0 *24, backward); // drive to middle point
  // wait until lift is ready
  // while (liftPot.get() < 90) pros::delay(20);
  driveToPoint(3 *24, 5 *24, backward);

  // wait until lift is ready
  Wait(1);
  clawBack.set_value(false);

  // 3: Get middle neutral
  Wait(0.25);

  driveForward(5);
  doUntil(t(driveToPoint(3 *24, 3 *24, backward)), r(clawBackButton.isPressed()));
  clawFront.set_value(true);

  // 4: Score middle neutral
  driveToPoint(3 *24, 4 *24, forward);
  // wait until lift is ready
  // while (liftPot.get() < 90) pros::delay(20);
  std::cout << "A" << std::endl;
  driveToPoint(3 *24, 5 *24, forward);
  std::cout << "B" << std::endl;
  clawFront.set_value(false);
  std::cout << "C" << std::endl;


  // --------------------- SLIDE 2 ---------------------
  // Get left blue

  driveForward(-5);
  std::cout << "D" << std::endl;
  driveToPoint(3 *24, 4 *24);
  driveToPoint(5 *24, 4 *24, forward);
  doUntil(t(driveToPoint(4.5 *24, 5.5 *24, forward)), r(clawFrontButton.isPressed()));
  clawFront.set_value(true);

  // --------------------- SLIDE 3 ---------------------
  // Get right blue with back side

  driveToPoint(5 *24, 4 *24);
  driveToPoint(1.5 *24, 4.5 *24, backward);
  lift.moveVoltage(-12000);
  doUntil(t(driveToPoint(0.5 *24, 4.5 *24, backward)), r(clawBackButton.isPressed()));
  // Back claw


  // --------------------- SLIDE 4 ---------------------
  // 1: Push left neutral to ready
  // 2: Drop blue to ready
  // 3: Score blue
  // 4: Retrieve blue
  // 5: Score blue
  // 6: Retrieve neutral
  // 7: Score neutral

  // 1: Push left neutral to ready
  driveToPoint(1 *24, 3.375 *24, forward);
  driveToPoint(3.25 *24, 1.5 *24, forward);

  // 2: Drop blue to ready
  driveToPoint(2.75 *24, 1.5 *24, backward);
  // Back claw release

  // 3: Score blue
  driveToPoint(3 *24, 1.5 *24);
  //liftTask.suspend();
  lift.moveVoltage(12000);
  turnToAngle(180);
  // wait until lift
  driveToPoint(3 *24, 1 *24, forward);
  clawFront.set_value(false);

  // 4: Retrieve blue
  driveForward(-3);
  lift.moveVoltage(-12000);
  driveForward(-5);
  turnToAngle(-90);
  // wait until lift
  doUntil(t(driveToPoint(2 *24, 1.5 *24, forward)), r(clawFrontButton.isPressed()));
  clawFront.set_value(true);

  // 5: Score blue
  lift.moveVoltage(12000);
  turnToPoint(3 *24, 1 *24);
  // wait until lift
  driveToPoint(3 *24, 1 *24, forward);
  clawFront.set_value(false);

  // 6: Retrieve neutral
  driveForward(-3);
  lift.moveVoltage(-12000);
  driveForward(-5);
  turnToAngle(90);
  // wait until lift
  doUntil(t(driveToPoint(3 *24, 1.5 *24, forward)), r(clawFrontButton.isPressed()));
  clawFront.set_value(true);

  // 7: Score neutral
  lift.moveVoltage(12000);
  turnToPoint(3 *24, 1 *24);
  // wait until lift
  driveToPoint(3 *24, 1 *24, forward);
  clawFront.set_value(false);


  // --------------------- SLIDE 5 ---------------------
  // 1: Get right red with back claw
  // 2: Get right neutral
  // 3: Drop red in ready
  // 4: Score neutral

  // 1: Get right red with back claw
  driveForward(-3);
  lift.moveVoltage(-12000);
  driveForward(-5);
  driveToPoint(5 *24, 2 *24);
  turnToPoint(5.5 *24, 1.5 *24, backward);
  doUntil(t(driveToPoint(5.5 *24, 1.5 *24, backward)), r(clawBackButton.isPressed()));
  // back clawBack

  // 2: Get right neutral
  doUntil(t(driveToPoint(4.5 *24, 3 *24, forward)), r(clawFrontButton.isPressed()));
  clawFront.set_value(true);
  //liftTask.resume();

  // 3: Drop red in ready
  driveToPoint(2.5 *24, 1.5 *24, backward);
  // release back

  // 4: Score neutral
  //liftTask.suspend();
  lift.moveVoltage(12000);
  turnToPoint(3 *24, 1 *24);
  // wait until lift
  driveToPoint(3 *24, 1 *24, forward);
  clawFront.set_value(false);

  // --------------------- SLIDE 6 ---------------------
  // 1: Retrieve red
  // 2: Score red

  // 1: Retrieve red
  driveForward(-3);
  lift.moveVoltage(-12000);
  driveForward(-5);
  turnToAngle(-90);
  // wait until lift
  doUntil(t(driveToPoint(2 *24, 1.5 *24, forward)), r(clawFrontButton.isPressed()));
  clawFront.set_value(true);

  // 2: Score red
  //liftTask.resume();
  driveToPoint((xPos+3 *24)/2.0, 3 *24, forward);
  //liftTask.suspend();
  lift.moveVoltage(12000);
  driveToPoint((xPos+3 *24)/2.0, 4.5 *24, forward);
  // wait until lift
  driveToPoint(3 *24, 5 *24, forward);
  clawFront.set_value(false);


  // ending
  driveForward(-3);
  lift.moveVoltage(-12000);
  driveForward(-10);
}

// void rightAuton(){
//
//   yPos = 5;
//
//   // Get First Tower
//   // groupMoveTo(clawFront, -1300, 0);
//   // Drive to tower
//   driveTargetTime = 0;
// 	driveToPoint(-1, 54.5, forward);
// 	driveTargetTime = prevDriveTargetTime;
//   pros::delay(250);
//   // clawFront.moveVoltage(-12000.0);
//   leftSide.moveVoltage(12000.0 * 0.05);
//   rightSide.moveVoltage(12000.0 * 0.7);
//   double startRot = rot;
//   while (!(clawFrontButton.isPressed() || rot < startRot - 30)) pros::delay(20);
//   leftSide.moveVoltage(0);
//   rightSide.moveVoltage(0);
//   pros::delay(250);
//   // clawFront.moveVoltage(12000.0);
//   pros::delay(1000);
//
//   // Part A: Get in position
//   goToPoint(-2, 23.5, backward);
//   lift.moveVoltage(-12000.0 * 0.9);
//   turnToAngle(-87);
//   // Part B: Drive and get tower in grip
//   driveForward(-8, -87);
//   groupMoveTo(clawBack, -2000);
//   pros::delay(250);
//   leftSide.moveVoltage(-12000.0 * 0.45);
//   rightSide.moveVoltage(12000.0 * 0.1);
//   int startTime = pros::millis();
//   while (!(clawBackButton.isPressed() || pros::millis() > startTime + 2000)) pros::delay(20);
//   leftSide.moveVoltage(0);
//   rightSide.moveVoltage(0);
//   // Part C: Secure tower in grip
//   groupMoveTo(clawBack, -2200, 0);
//   driveForward(-1);
//   groupMoveTo(lift, 700, 0, PID(15, 0, 0), 50, 10000);
//   pros::delay(500);
//
//   // Drive to end position
//   driveToPoint(-26, 24, best);
// }
//
// void leftAuton(){
//
//   xPos = 29.5;
// 	yPos = 15.5;
//
//   // grabTower({36, 72});
//   // return;
//
//   // Get First Tower
//   // groupMoveTo(clawFront, -1300, 0);
//   // Drive to tower
//   driveTargetTime = 0;
// 	driveToPoint(38, 65.75, forward);
//   // Turn into tower
//   pros::delay(250);
//   // clawFront.moveVoltage(-12000.0);
//   leftSide.moveVoltage(12000.0 * 0.05);
//   rightSide.moveVoltage(12000.0 * 0.7);
//   double startRot = rot;
//   while (!(clawFrontButton.isPressed() || rot < startRot - 30)) pros::delay(20);
//   leftSide.moveVoltage(0);
//   rightSide.moveVoltage(0);
//   pros::delay(250);
//   // clawFront.moveVoltage(12000.0);
//   pros::delay(1000);
//
//   // Get Middle Tower
//   groupMoveTo(clawBack, -1700, 0);
//   driveTargetTime = 0;
//   turnTargetError = 5;
//   goToPoint(48, 58, backward);
//   goToPoint(64, 58, backward);
//   turnTargetError = prevTurnTargetError;
//   lift.moveVoltage(-12000.0);
//   // point tower1 = findOffsetTarget({xPos, yPos}, {72, 72}, {7, -10.5});
//   // prevDriveTargetTime = driveTargetTime; driveTargetTime = 0;
//   // turnToPoint(tower1.x, tower1.y, backward);
//   grabTower({72, 72}, backward, {5, -10.5});
//   // Turn into tower
//   pros::delay(250);
//   leftSide.moveVoltage(-12000.0 * 0.4);
//   rightSide.moveVoltage(12000.0 * 0.1);
//   clawBack.moveVoltage(-12000.0 * 0.125);
//   int startTime = pros::millis();
//   while (!(clawBackButton.isPressed() || pros::millis() > startTime + 3000)) pros::delay(20);
//   leftSide.moveVoltage(0);
//   rightSide.moveVoltage(0);
//   pros::delay(1000);
//   clawBack.moveVoltage(12000.0);
//   pros::delay(1000);
//   lift.moveVoltage(0);
//
//   driveToPoint(39.5, 40.5);
//   driveToPoint(29.5, 23.5);
//   driveTargetTime = prevDriveTargetTime;
// }
//
// void skills(){
//
//   // xPos = 72;
//   // yPos = 96;
//
//   xPos = 16;
//   yPos = 10.5;
//
//   iSensor.set_rotation(90);
//   rot = 90;
//   prevRot = 90 * (pi / 180);
//
//   // Get left red
//   groupMoveTo(clawFront, -1300, 0);
//   lift.moveVoltage(-12000.0 * 0.9);
//   driveForward(13);
//   // Turn into tower
//   pros::delay(250);
//   clawFront.moveVoltage(-12000.0 * 0.25);
//   leftSide.moveVoltage(12000.0 * 0.05);
//   rightSide.moveVoltage(12000.0 * 0.5);
//   double startRot = rot;
//   while (!(clawFrontButton.isPressed() || rot < startRot - 80)) pros::delay(20);
//   clawFront.moveVoltage(-12000.0);
//   leftSide.moveVoltage(0);
//   rightSide.moveVoltage(0);
//   pros::Task liftTask = groupMoveTo(lift, 1000, 0, PID(0.1, 0.001, 0, 10000, -1), -1);
//   pros::delay(250);
//
//   // move left neutral tower to top right
//   driveTargetTime = 0;
//   driveForward(-10);
//   // pros::delay(1000);
//   driveToPoint(xPos + 2, yPos + 10, forward);
//   //pros::delay(250);
//   double angle = findRotationTo(xPos, yPos, 18, 60) + 180;
//   turnToAngle(angle, 0.5);
//   pros::delay(250);
//   driveToPoint(18, 60, backward);
//   driveTargetTime = 1000;
//   driveTargetError = 30;
//   turnTargetError = 3;
//   turnToPoint(78, 110, backward);
//   pros::Task speedTask([&](){
//     driveStrength = 0.5;
//     pros::delay(1000);
//     driveStrength = 1;
//   });
//   driveToPoint(74, 112, backward);
//   driveTargetTime = 0;
//   driveTargetError = prevDriveTargetError;
//   turnTargetError = prevTurnTargetError;
//   liftTask.suspend();
//
//   // score left red on platform
//   driveToPoint(70, 100, forward);
//   lift.moveVoltage(12000.0);
//   turnToAngle(0);
//   driveTargetTime = 1000;
//   driveTargetError = 25;
//   driveForward(30);
//   driveTargetTime = 0;
//   driveTargetError = prevDriveTargetError;
//   clawFront.moveVoltage(12000.0);
//   pros::delay(1000);
//   driveForward(-24);
//   lift.moveVoltage(-12000.0);
//   pros::delay(500);
//
//   // get right blue
//   groupMoveTo(clawFront, -1300, 0);
//   turnToAngle(-90);
//   driveForward(36);
//   // driveToPoint(36, 114, forward);
//   pros::Task moveTask([&](){
//     grabTower({12, 108}, forward, {2, -6});
//     while(true) pros::delay(1000);
//   });
//   pros::delay(2000);
//   moveTask.suspend();
//   leftSide.moveVoltage(12000.0 * -0.3);
//   rightSide.moveVoltage(12000.0 * 0.5);
//   while (rot > findShortestRotation(rot, -70) && !clawFrontButton.isPressed()) pros::delay(20);
//   leftSide.moveVoltage(0);
//   rightSide.moveVoltage(0);
//   // Turn into tower
//   // pros::delay(250);
//   leftSide.moveVoltage(12000.0 * 0.05);
//   rightSide.moveVoltage(12000.0 * 0.5);
//   startRot = rot;
//   while (!(clawFrontButton.isPressed() || rot < startRot - 80)) pros::delay(20);
//   clawFront.moveVoltage(-12000.0);
//   leftSide.moveVoltage(0);
//   rightSide.moveVoltage(0);
//   liftTask = groupMoveTo(lift, 1000, 0, PID(0.1, 0.001, 0, 10000, -1), -1);
//   pros::delay(1000);
//   // drive backwards after get tower
//
//   // move middle neutral
//   driveToPoint(48, 96, backward);
//   driveToPoint(114, 36, backward);
//
//   // score right blue on platform
//   driveForward(24);
//   driveToPoint(74, 48, forward);
//   liftTask.suspend();
//   lift.moveVoltage(12000.0);
//   turnToAngle(180);
//   driveTargetTime = 1000;
//   driveTargetError = 25;
//   driveForward(30);
//   driveTargetTime = 0;
//   driveTargetError = prevDriveTargetError;
//   clawFront.moveVoltage(12000.0);
//   pros::delay(1000);
//   driveToPoint(72, 50, backward);
//   lift.moveVoltage(-12000.0);
//
//   // get right red
//   groupMoveTo(clawFront, -1300, 0);
//   driveToPoint(100, 36, forward);
//   driveTargetTime = 1000;
//   driveTargetError = 15;
//   grabTower({132, 36}, forward, {2, -10});
//   driveTargetTime = 0;
//   driveTargetError = prevDriveTargetError;
//   leftSide.moveVoltage(12000.0 * 0.05);
//   rightSide.moveVoltage(12000.0 * 0.5);
//   while (rot > findShortestRotation(rot, -90) && !clawFrontButton.isPressed()) pros::delay(20);
//   leftSide.moveVoltage(0);
//   rightSide.moveVoltage(0);
//   // Turn into tower
//   pros::delay(250);
//   leftSide.moveVoltage(12000.0 * 0.05);
//   rightSide.moveVoltage(12000.0 * 0.5);
//   startRot = rot;
//   while (!(clawFrontButton.isPressed() || rot < startRot - 80)) pros::delay(20);
//   clawFront.moveVoltage(-12000.0);
//   leftSide.moveVoltage(0);
//   rightSide.moveVoltage(0);
//   liftTask = groupMoveTo(lift, 1000, 0, PID(0.1, 0.001, 0, 10000, -1), -1);
//   pros::delay(1000);
//
//   // move right neutral
//   driveToPoint(108, 48, backward);
//   driveToPoint(108, 100, backward);
//
//   // score right red on platform
//   driveForward(5);
//   driveToPoint(68, 96, forward);
//   lift.moveVoltage(12000.0);
//   turnToAngle(0);
//   driveTargetTime = 1000;
//   driveTargetError = 25;
//   driveForward(30);
//   driveTargetTime = 0;
//   driveTargetError = prevDriveTargetError;
//   clawFront.moveVoltage(12000.0);
//   pros::delay(1000);
//   driveToPoint(72, 96, backward);
//   lift.moveVoltage(-12000.0);
//   pros::delay(10000);
// }

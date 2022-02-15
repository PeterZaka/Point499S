#include "auton-config.hpp"

// ------- Drive -------
// Drive Strength - Max strength of drive, 0 to 1 (0% to 100%)
double driveStrength = 1;

// Drive Target Time - Amount of time (in seconds) needed within target error for driving
double driveTargetTime = 0.25;

// Drive Target Error - Be within distance (in inches) to be on target
double driveTargetError = 3;

// Stop
// Drive Stop Time - Amount of time (in seconds) needed within stop error for driving
double driveStopTime = 1;

// Drive Stop Error - Be within distance (in inches) after driveStopInterval seconds to be stopped
double driveStopError = 3;

// Drive Stop Interval - Time interval to measure if stopped
double driveStopInterval = 0.25;


// ------- Turn -------
// Turn Target Time - Amount of time (in seconds) needed within target error for turning
double turnTargetTime = 0.25;

// Turn Target Error - Be within rotation (in degrees) to be on target
double turnTargetError = 1;

// Correct Rotation Error - Be outside distance (in inches) to change rotation
double correctRotationError = 3;

// Slow Down Rotation Error - Be inside distance (in inches) to slow rotation
double slowDownRotationError = 8;

// Stop
// Turn Stop Time - Amount of time (in seconds) needed within stop error for turning
double turnStopTime = 1;

// Turn Stop Error - Be within rotation (in degrees) after turnStopInterval seconds to be stopped
double turnStopError = 0.05;

// Turn Stop Interval - Time interval to measure if stopped
double turnStopInterval = 0.25;


// ------- Color -------
// Min Color Width - Minimum width for an object to be detected
double minColorWidth = 50;

// Min Color Height - Minimum height for an object to be detected
double minColorHeight = 10;

// Color Strength - Max strength of how much it steers to color, 0 to 1 (0% to 100%)
double colorStrength = 1;

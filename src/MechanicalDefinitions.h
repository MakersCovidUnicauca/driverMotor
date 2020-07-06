#ifndef MECHANICAL_DEF
#define MECHANICAL_DEF

#include "PinOutMotor.h"

///////////////////////////////////   Stepper Motor
//////////////////////////////////////////////////

#include <AccelStepper.h>
// The X Stepper pins
#define PulsePerRev 8000
#define mmPerRev 72
#define mmPerPulse 0.009
#define PulseXmm 111.111

#define DelayPulse 220 // millisecond
#define LONG_FUELLE 60 //milimetros (mm)
#define RELMMVOL 17.67

float mPosInit = 0;          // mm
float mPosEnd = LONG_FUELLE; // mm
float mPosCurrent;           // mm
float mPosOxi = 0;           // mm
float mPosVol = 0;


//diametro 15 cm
//area 176 cm2
//1.76 ml * ml

#define DIST_MOTOR 60    // mm
#define VEL_MOTOR 30.0   // mm/s
#define ACCEL_MOTOR 30.0 // mm/s2
#define INITPOSITION 0
#define BACKINITPOS INITPOSITION + 500

#define MAX_ACCEL 10000
#define MAX_SPEED 20000

#define InitSensorEnable

float DistMotor = DIST_MOTOR;
float VelMotor = VEL_MOTOR;    // mm/s
float AcelMotor = ACCEL_MOTOR; // mm/s2

AccelStepper Motor(AccelStepper::DRIVER, STEPPER1_STEP_PIN, STEPPER1_DIR_PIN);

#endif
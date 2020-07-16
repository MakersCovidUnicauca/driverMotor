#ifndef MotorDirver_h
#define MotorDirver_h




long currentMicros = 0; 
long previousMicros = 0;
#define minMicroStepDelay 20
#define InitialSpeedMotor 1000
// Vars on Motor Driver
boolean MotorRuning = 0;  // FLag motor is running
long targetPos = 0;        // Target position
long currentPos = 0;       // current position
long currentSpeed = InitialSpeedMotor;     // current speed
long targetSpeed = InitialSpeedMotor;      // target speed
long delayMicrosMotor = 1000000/InitialSpeedMotor;     // Set value
boolean directionMotor = 0;
#define delayTimeTarget 500



//new Library motor
void setCurrentPositionM(long position);
long currentPositionM();
void setMaxSpeedM(long speedM);
void setAccelerationM(long accel );
boolean MotorMoveTo(long DistanceValue);
void RunMotor();
void stopMotor();
#endif
/*!
\file   MotorVent.ino
\date   2020-05-05
\author Fulvio Vivas <fulvio.vivas@gmail.com>
\brief  Functions Motor.

\par Copyright
Information contained herein is proprietary to and constitutes valuable
confidential trade secrets of XXXXXX, and
is subject to restrictions on use and disclosure.

\par
Copyright (c) XXXXX 2020. All rights reserved.

\par
The copyright notices above do not evidence any actual or
intended publication of this material.
******************************************************************************
*/

/*F**************************************************************************
* NAME: refMotor
*----------------------------------------------------------------------------
* PARAMS:
* return:   none
*----------------------------------------------------------------------------
* PURPOSE:
* Search Motor Reference Position
*----------------------------------------------------------------------------
* NOTE:
* 
*****************************************************************************/
#include "Definitions.h"

#define refDistance -70.0 * PulseXmm
#define refSpeed 10.0 * PulseXmm
#define refAccel 10.0 * PulseXmm

void refMotor()
{
  // Busqueda posicion de inicio
  digitalWrite(STEPPER1_ENA_PIN, LOW); //

#ifdef InitSensorEnable
  //DEBUG("Searching position ");
  setCurrentPositionM(0);
  //DEBUG(GetPosition());
  SetMotor(refDistance, refSpeed, refAccel);
  //Search Initial Position
  while (digitalRead(OPTICAL_SENSOR_0) != HIGH)
  {
    RunMotor();
    delay(1);
  }
  InitMotor(INITPOSITION); //Define 0 position
  //DEBUG("Entering back ");
  // go to initial position + 5
  SetMotor(500, refSpeed, refAccel);
  while (MotorRuning > 0)
  {
    RunMotor();
    delay(1);
  }
#ifdef __DEBG__
  //DEBUG("Got position ");
  //Serial.println(GetPosition());
#endif
  //return to Initial position
  SetMotor(INITPOSITION, refSpeed / 2, refAccel / 2);
  DEBUG1("OK,00");
  while (digitalRead(OPTICAL_SENSOR_0) != HIGH)
  {
    RunMotor();
    delay(1);
  }
  InitMotor(INITPOSITION); //Define 0 position
#else
  digitalWrite(STEPPER1_ENA_PIN, HIGH); //
  delay(1000);
  while (digitalRead(HALL_SENS_PIN) != HIGH)
  {
    delay(1000);
    DEBUG("waiting position ");
  }
  InitMotor(INITPOSITION); //Define 60 position
  Serial.println(GetPosition());
#endif
// Enable Motor
digitalWrite(STEPPER1_ENA_PIN, LOW); //Serial.println 

}

/*F**************************************************************************
* NAME: GetPosition
*----------------------------------------------------------------------------
* PARAMS:
* paramt: none
* return: Current Position of Motor
* *----------------------------------------------------------------------------
* PURPOSE:
* Get Motor Position
*----------------------------------------------------------------------------
* NOTE:
* Monitor Current Position in the Ventilator Operation
*****************************************************************************/

long GetPosition()
{
  long positionMotor = 0;
  positionMotor = currentPositionM();
  return positionMotor;
}

/*F**************************************************************************
* NAME: InitMotor
*----------------------------------------------------------------------------
* PARAMS:
* return:   none
*----------------------------------------------------------------------------
* PURPOSE:
* Initialize Motor at initial position
* *----------------------------------------------------------------------------
* NOTE:
* 
*****************************************************************************/
void InitMotor(long Init_position)
{
  setCurrentPositionM(Init_position );
  
}

/*F**************************************************************************
* NAME: SetMotor
*----------------------------------------------------------------------------
* PARAMS:
* Distance: Motor Target Position
* speedM: Motor Speed
* accel: Motor Acceleration
* return:   none
*----------------------------------------------------------------------------
* PURPOSE:
* Set Motor Configuration Parameters
*----------------------------------------------------------------------------
* NOTE:
* 
*****************************************************************************/
void SetMotor(long Distance, long speedM, long accel)
{
  digitalWrite(STEPPER1_ENA_PIN, LOW); //Deshabilitar Motor
  long DistanceValue = (long)Distance ;
  setMaxSpeedM(speedM );
  setAccelerationM(accel );
  MotorMoveTo(DistanceValue);  
}

/*F**************************************************************************
* NAME: updateMotorPos
*----------------------------------------------------------------------------
* PARAMS:
* return:   none
*----------------------------------------------------------------------------
* PURPOSE:
* Update Motor Position
* *----------------------------------------------------------------------------
* NOTE:
* 
*****************************************************************************/
void updateMotorPos()
{
  long dist = GetPosition();
  if (mPosCurrent != dist)
  {
    if(CheckAlarm){
      if(dist <= AlarmPos){
        DEBUG1("A,"+String(AlarmPos));
        CheckAlarm = 0;
      }
    }
    String stringone = "Dist:";
    stringone = stringone + String(dist);
    mPosCurrent = dist;
    if(MotorRuning == 0){
      if(CheckPos){
        CheckPos = 0;
        if(refZero){
          refZero = 0;
          RefZeroMotor();
    
        }
        DEBUG1("ACK,1");
      }
      }
      else{
        if(refZero){
           if(digitalRead(OPTICAL_SENSOR_0) == HIGH){
            refZero = 0;
            stopMotor();
            setCurrentPositionM(INITPOSITION); //Define 0 position
            DEBUG1("ACK,1");
          }
        }
      }
    
  }
}



void RefZeroMotor(){
  if(digitalRead(OPTICAL_SENSOR_0) != HIGH){
    MotorMoveTo(refDistance);
    //Search Initial Position
    while (digitalRead(OPTICAL_SENSOR_0) != HIGH)
    {
      RunMotor();
      delayMicroseconds(50);
    }
    setCurrentPositionM(INITPOSITION); //Define 0 position
    }    
}
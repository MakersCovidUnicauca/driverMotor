#include "Definitions.h"


void setCurrentPositionM(long position){
    currentPos = position;
    CheckPos = 0;
    refZero = 0;
    MotorRuning = 0;
}

long currentPositionM(){
    return currentPos;
}

void setMaxSpeedM(long speedM){
    targetSpeed = speedM;
}

void setAccelerationM(long accel ){
   // byte varMotor = 0;
}

boolean MotorMoveTo(long DistanceValue){
    targetPos = DistanceValue;
    if(targetPos != currentPos){
        
        if((targetPos-currentPos)<0){
            directionMotor = 1;
        }
        else{
            directionMotor = 0;
        }
        delayMicrosMotor = long(1000000/targetSpeed);
        if(delayMicrosMotor < minMicroStepDelay){
            delayMicrosMotor = minMicroStepDelay;
        }
        MotorRuning = 1;
        currentMicros = micros();
        return 0;
    }
    else{
        return 1;
    }
}

void stopMotor(){
    MotorRuning = 0;
}





void RunMotor()
{
    if(MotorRuning){
        digitalWrite(STEPPER1_ENA_PIN, LOW); //Deshabilitar Motor
        currentMicros = micros();
        while((currentMicros - previousMicros) >= delayMicrosMotor)
        {
            digitalWrite(STEPPER1_DIR_PIN,directionMotor);
            digitalWrite(STEPPER1_STEP_PIN,HIGH);
            delayMicroseconds(minMicroStepDelay); //Set minimal delay time
            digitalWrite(STEPPER1_STEP_PIN,LOW);

            if(directionMotor){
                currentPos--;
            }
            else{
                currentPos++;
            }
            if(currentPos == targetPos){
              MotorRuning=0;
              digitalWrite(STEPPER1_ENA_PIN,LOW);
              delayMicroseconds(delayTimeTarget);
              break;

            }
            previousMicros = currentMicros;

        }
    }
    else{
        delay(1);
        digitalWrite(STEPPER1_ENA_PIN, HIGH); //Deshabilitar Motor
    }
 }
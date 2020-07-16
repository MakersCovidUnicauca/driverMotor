
// I2C comunication 


#include "Definitions.h"



void InitComunicationMotor(){
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);

}

void CheckCommand(){

// check if data has been sent from the computer:
  if (stringComplete) {
    stringComplete = false;
    char command = inputString[0];
    long nextPos = 0;
    boolean result = 0;
    switch (command)
    {
    case 'A':  // Reportar alarma
      inputString[0] = '0';
      result = CheckStringIn();
        if(result){
        AlarmPos = inputString.toInt();
        if(AlarmPos > 6700){
           AlarmPos = 6700;
          }
        CheckAlarm = 1;
        DEBUG1("OK,"+String(AlarmPos));
      }
    break;
    case 'V': // Definir velocidad
      inputString[0] = '0';
      result = CheckStringIn();
        if(result){
        speedMotor  = inputString.toInt();
        if(speedMotor > MAX_SPEED){
          speedMotor = MAX_SPEED;
        }
        setMaxSpeedM(speedMotor);
        saveVarMotor();
        
        DEBUG1("OK,"+String(speedMotor));
      }
    break;
    case 'B': // Definir Aceleracion
      inputString[0] = '0';
      result = CheckStringIn();
        if(result){
        accelMotor  = inputString.toInt();
        if(accelMotor > MAX_ACCEL){
          accelMotor = MAX_ACCEL;
        }
        saveVarMotor();
        DEBUG1("OK,"+String(accelMotor));
      }
    break;
    case 'S': // Detener motor
        stopMotor();
        DEBUG1("OK,STOP");
    break;
    case 'Q': // Consultar posicion
        DEBUG1("D,"+String(GetPosition()));
    break;
    case 'E': // Consultar posicion
        DEBUG1("E,"+String(targetSpeed)+","+String(delayMicrosMotor));
    break;
    case 'R': // Consultar posicion
        refMotor(); //busca el sensor optico  solo inicio
        DEBUG1("R,0");
    break;
    case 'P': //Fijar Posicion
        inputString[0] = '0';
        result = CheckStringIn();
        if(result){
          nextPos  = inputString.toInt();
          if(nextPos > 6700){
            nextPos = 6700;
          }
          if(nextPos == 0){
            refZero = 1;
          }
          MotorMoveTo(nextPos);
          CheckPos = 1;
          DEBUG1("OK,"+String(nextPos));
        }
        
    break;
    
    default:
        DEBUG1("NACK,0");
    break;
    }
    inputString = "";
    
    // read the most recent byte (which will be from 0 to 255):
    
  }
}

  /*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}


boolean CheckStringIn(){
 //DEBUG("Check "+ inputString +" "+ String(inputString.length()));
 byte stringLength = inputString.length()-2;
 for(byte i=0; i< stringLength;i++){
   if( inputString[i]<'0' || inputString[i] > '9' ) {
    //DEBUG("Not digit ");
    return false;
    }
  }
  return true;
}
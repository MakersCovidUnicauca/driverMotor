
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
    int nextPos = 0;
    switch (command)
    {
    case 'A':  // Reportar alarma
      inputString[0] = '0';
      if(CheckString(inputString)){
        AlarmPos = inputString.toInt();
        CheckAlarm = 1;
        DEBUG("OK,"+String(AlarmPos));
      }
    break;
    case 'V': // Definir velocidad
      inputString[0] = '0';
      if(CheckString(inputString)){
        speedMotor  = inputString.toInt();
        if(speedMotor > MAX_SPEED){
          speedMotor = MAX_SPEED;
        }
        saveVarMotor();
        
        DEBUG("OK,"+String(speedMotor));
      }
    break;
    case 'B': // Definir Aceleracion
      inputString[0] = '0';
      if(CheckString(inputString)){
        accelMotor  = inputString.toInt();
        if(accelMotor > MAX_ACCEL){
          accelMotor = MAX_ACCEL;
        }
        saveVarMotor();
        DEBUG("OK,"+String(accelMotor));
      }
    break;
    case 'S': // Detener motor
        Motor.stop();
        DEBUG("OK,STOP");
    break;
    case 'Q': // Consultar posicion
        DEBUG("D,"+String(GetPosition()));
    break;
    case 'P': //Fijar Posicion
        inputString[0] = '0';
        if(CheckString(inputString)){
          nextPos  = inputString.toInt();
          if(nextPos > 6700){
            nextPos = 6700;
          }
          if(nextPos == 0){
            refZero = 1;
          }
          SetMotor(nextPos, speedMotor, accelMotor);
          CheckPos = 1;
          DEBUG("OK,"+String(nextPos));
        }
        
    break;
    
    default:
        DEBUG("NACK");
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


boolean CheckString(String str){
 for(byte i=0; i< str.length();i++){
   if( !isDigit(str[i])) {
    //Serial.println("Not digit");
    return false;
    }
  }
  return true;
}

#include "Definitions.h"

//Write the value to the appropriate byte of the EEPROM.
void saveVarMotor(){
    // Var Motor
float accelMotor = 1000;
float speedMotor = 500; 
long AlarmPos = 1000;
  EEPROM.put(0, AlarmPos);
  EEPROM.put(8, accelMotor);
  EEPROM.put(16, speedMotor);
  byte initEpprom = 0x07;
  EEPROM.put(24, initEpprom);
}

// read a byte from the current address of the EEPROM
// It uses a general eeprom library
void readVarMotor(){
  byte initEpprom = 0x07;
  EEPROM.get(18, initEpprom);
 if(initEpprom == 0x07){
    EEPROM.get(0, AlarmPos);
    EEPROM.get(8, accelMotor);
    EEPROM.get(16, speedMotor);
 }
 else{
     AlarmPos = 0;
     accelMotor = 8000;
     speedMotor = 1000;
 }
}

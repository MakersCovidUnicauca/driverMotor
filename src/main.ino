#include "Definitions.h"

/////////////////////////////////////////
void setup()
{
  while (!Serial)
  {
    ;
  }
  Serial.begin(115200);
  Wire.begin(); // join i2c bus (address optional for master)
  delay(1000);
  //EEPROM
  EEPROM.begin(EEPROM_SIZE);
  DEBUG("Init Motor");
  readVarMotor();
  pinMode(INBUILD_LED,OUTPUT);
  pinMode(STEPPER1_STEP_PIN, OUTPUT);
  pinMode(STEPPER1_DIR_PIN, OUTPUT);
  pinMode(STEPPER1_ENA_PIN, OUTPUT);
  //directionInvert,stepInvert,enableInvert
  //Motor.setPinsInverted(true, false,false);
  //Optical Sensor
  pinMode(OPTICAL_SENSOR_0, INPUT_PULLUP);
  pinMode(OPTICAL_SENSOR_1, INPUT_PULLUP);
  pinMode(CNY70_SENSOR,INPUT_PULLUP);
  //Disable motor
  digitalWrite(INBUILD_LED,HIGH);
  digitalWrite(STEPPER1_ENA_PIN, HIGH); //Deshabilitar Motor

  //Init I2c
  msg2Web.reserve(700);
  InitComunicationMotor();
  // Motor Conf
  DEBUG("Serching Motor");
  refMotor(); //busca el sensor optico  solo inicio
  //DEBUG("Finish Motor");
}

void loop()
{
  // indica la posicion via Serial
  updateMotorPos();
  //Funcion para actualizacion de pasos del motor
  RunMotor();

  //serial Events
  serialEvent();
  CheckCommand();
  VolumenData();

}

void VolumenData(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval){
    volUser[posVolumen] = GetPosition();
    posVolumen++;
    if(posVolumen > DataGraphic)
    {
      posVolumen = 0;
      msg2Web = "D";
      for (int i = 0; i <= DataGraphic; i ++)
        {
          int VolumenUser = volUser[i];
          msg2Web += "," + String(VolumenUser);
        }
      if(sendPosition){
        DEBUG1(msg2Web);
      } 
      else{
         DEBUG1("D,"+String(GetPosition()));
      } 
      
     
    }
    previousMillis = currentMillis;
  }
}

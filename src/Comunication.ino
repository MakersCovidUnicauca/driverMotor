
// I2C comunication

#include "Definitions.h"

void InitComunicationMotor()
{
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void CheckCommand()
{


}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent()
{
  while (Serial.available())
  {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n')
    {
      stringComplete = true;
    }
  }
}

boolean CheckStringIn()
{
  //DEBUG("Check "+ inputString +" "+ String(inputString.length()));
  byte stringLength = inputString.length() - 2;
  for (byte i = 0; i < stringLength; i++)
  {
    if (inputString[i] < '0' || inputString[i] > '9')
    {
      //DEBUG("Not digit ");
      return false;
    }
  }
  return true;
}
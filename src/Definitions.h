
#ifndef Definitions_h
#define Definitions_h

#include <Arduino.h>
#include <Wire.h>
//Memoria EEPROM
#include <EEPROM.h>
#define EEPROM_SIZE 100
//Definicion de pines
#include "PinOutMotor.h"
//Parametros mecanicos
#include "MechanicalDefinitions.h"

#define AddresI2C   0x08
byte SlaveReceived = 0;


#define __DEBG__

#ifdef __DEBG__
#define DEBUG(a)            \
    Serial.print(millis()); \
    Serial.print("- ");     \
    Serial.println(a);
#else
String TestString;
#define DEBUG(a)  TestString = String(a);
#endif

// Var Motor
float accelMotor = 1000;
float speedMotor = 500; 
long AlarmPos = 1000;

boolean CheckAlarm = 0;
boolean CheckPos = 0;
boolean refZero = 0;


unsigned long previousMillis = 0;        // will store last time LED was updated
unsigned long FirstMillis = 0; 
const long interval = 20;
#define TimeSendGraphic 60
#define DataGraphic 49
long volUser[TimeSendGraphic];
int posVolumen = 0;
String msg2Web;


// motor library
void refMotor(); 
long GetPosition();
void updateMotorPos();
void SetMotor(long Distance, float speedM, float accel);

// Comunication
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
void InitComunicationMotor();
void serialEvent();
void CheckCommand();

//Eeprom
void readVarMotor();
void saveVarMotor();

#endif
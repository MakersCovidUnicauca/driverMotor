//﻿#define __Other__
//#define Arduino_PCB
#ifndef PINOUT_BOARDS
#define PINOUT_BOARDS

#define ESP32_PCB

#ifdef ESP32_PCB


//Motor
#define STEPPER1_STEP_PIN 0
#define STEPPER1_DIR_PIN 4
#define STEPPER1_ENA_PIN 16

#define INBUILD_LED 5

//Finales de Carrera

#define OPTICAL_SENSOR_0 36     // Finales de carrera posicion 0
#define OPTICAL_SENSOR_1 39     // Finales de carrera posicion fin


#endif


#ifdef __Other__
#define KEY_R1_PIN 10
#define KEY_R2_PIN 9
#define KEY_R3_PIN 8
#define KEY_R4_PIN 7
#define KEY_C1_PIN 6
#define KEY_C2_PIN 5
#define KEY_C3_PIN 4

//#define BUZZ_ALARM_PIN 6
#define HALL_SENS_PIN 11 // siempre debe estar
#define VALV_OXIG_PIN 13 // siempre debe estar
#define VALV_EXTR_PIN A3 // siempre debe estar
#define STEPPER1_ENA_PIN A3
#define STEPPER1_STEP_PIN 3
#define STEPPER1_DIR_PIN 2

#define BTN_CFG_PIN 12
#define PRESS_OXIG_PIN A2
#define PRESS_USR_PIN A1
#define PRESS_AMBU_PIN A0

//encoder
#define ENCODER_DT_PIN  12
#define ENCODER_SW_PIN  A3
#define ENCODER_CLK_PIN  11


#endif

#endif
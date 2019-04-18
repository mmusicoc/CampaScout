#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <Arduino.h>
#include "Debug.hpp"

// Parámetros del programa
#define PARAMFILE       "Paramets.txt"
#define LOGFILE         "Datalog.csv"
#define BAUDRATE        9600
#define CORE_LOOPS      30
#define LOOP_DELAY      50
#define LED_BLINK       750
#define READ_DELAY      20
#define START_COUNT     3

// Pines
#define FLOWMETER       2
#define SENSOR_MIN      A6
#define SENSOR_MAX      A7
#define SWITCH_COUNT    3
#define SWITCH_PINS     A0,A1,A2            // En orden: AUTO (B1), MANUAL (B2), DEBUG (B3)
#define CHIP_SELECT     4
#define RELAY           13
#define LED_COUNT       5
#define LED_PINS        5,6,7,8,9           // En orden: NIVEL BAJO (L1), NIVEL MEDIO (L2), NIVEL ALTO (L3), MANUAL (L4), AUTO (L5)
#define RELAY_ON        LOW
#define RELAY_OFF       HIGH

#endif

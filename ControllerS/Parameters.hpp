#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <Arduino.h>
#include "Debug.hpp"

#define BAUDRATE        38400

// Pines
#define SENSOR_MIN      A6
#define SENSOR_MAX      A7
#define SWITCH_COUNT    3
#define SWITCH_PINS     A0,A1,A2              // En orden: AUTO (B1), MANUAL (B2), DEBUG (B3)

#define RELAY           13
#define LED_COUNT       5
#define LED_PINS        5,6,7,8,9           // En orden: NIVEL BAJO (L1), NIVEL MEDIO (L2), NIVEL ALTO (L3), MANUAL (L4), AUTO (L5)

// Parámetros del programa
#define CORE_LOOP       30
#define DELAY_LOOP      50
#define LED_BLINK       750
#define LIMIT_SENSOR    1020
#define CONTROL_SENSOR  50
#define READ_MARGIN     20

#define DEBUG_COUNT     2

// Modo de uso I/O
#define RELAY_ON        LOW
#define RELAY_OFF       HIGH

#endif

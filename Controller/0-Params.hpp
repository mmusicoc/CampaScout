#ifndef PARAMETERS_H
#define PARAMETERS_H

#include "Debug.hpp"

// EEPROM PATHS - Direcciones de memoria donde se guardan los parámetros para que cada vez que se inicie el Arduino se carguen
#define MEM_CHECKS 0                                              // int
#define MEM_LIMIT MEM_CHECKS + sizeof(int)                        // int

// Parámetros del programa
#define BAUDRATE        9600
#define CORE_LOOPS      30
#define LOOP_DELAY      50
#define LED_BLINK       750
#define READ_DELAY      20                  // Microsegundos entre lecturas consecutivas, para mitigar ruido.
#define TIMER_SEC       19                  // Loops de timer para un segundo, estimados con déficit.

// Pines
#define SENSOR_MIN      A6 
#define SENSOR_MAX      A7
#define SWITCH_COUNT    2
#define SWITCH_PINS     A0,A1               // En orden: AUTO (B1), MANUAL (B2), DEBUG (B3)
#define RELAY           13
#define LED_COUNT       5
#define LED_PINS        5,6,7,8,9           // En orden: NIVEL BAJO (L1), NIVEL MEDIO (L2), NIVEL ALTO (L3), MANUAL (L4), AUTO (L5)
#define RELAY_ON        LOW
#define RELAY_OFF       HIGH

// Quedan libres 3, 10, A3

//Parámetros por defecto
#define DEF_CHECKS      20
#define DEF_LIMIT       1000

#endif

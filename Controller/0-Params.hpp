#ifndef PARAMETERS_H
#define PARAMETERS_H

#include "Debug.hpp"

// EEPROM CAMINHOS - Endereços de memória onde os parâmetros são armazenados para que toda vez que o Arduino iniciar eles sejam carregados
#define MEM_CHECKS 0                                              // int
#define MEM_LIMIT MEM_CHECKS + sizeof(int)                        // int

// Parámetros del programa
#define BAUDRATE        9600
#define CORE_LOOPS      30
#define LOOP_DELAY      50
#define LED_BLINK       750
#define READ_DELAY      20                  // Microssegundos entre leituras consecutivas, para mitigar o ruído.
#define TIMER_SEC       19                  // O cronômetro faz um loop de um segundo, estimado com déficit.

// Pines
#define SENSOR_MIN      A6 
#define SENSOR_MAX      A7
#define SWITCH_COUNT    2
#define SWITCH_PINS     A0,A1               // Ordem: AUTO (B1), MANUAL (B2), DEBUG (B3)
#define RELAY           13
#define LED_COUNT       5
#define LED_PINS        5,6,7,8,9           // Em ordem: NÍVEL BAIXO (L1), NÍVEL MÉDIO (L2), NÍVEL ALTO (L3), MANUAL (L4), AUTO (L5)
#define RELAY_ON        LOW
#define RELAY_OFF       HIGH

// Permanecem livres 3, 10, A3

//Parâmetros padrão
#define DEF_CHECKS      20
#define DEF_LIMIT       1000

#endif

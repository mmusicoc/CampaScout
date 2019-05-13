#ifndef CONTROLLER_STATUS_H
#define CONTROLLER_STATUS_H

#include "Parameters.hpp"

typedef enum Level {underMin = 0, midLevel = 1, overMax = 2} level;     // Definición de tipos de estado posibles para el nivel de agua.
typedef enum LedState {off = 0, on = 1, blinky = 2} LEDstate;           // Definición de tipos de estado posibles para un LED.

class ControllerStatus{
  public:
  // CONSTRUCTOR
    ControllerStatus();

  // METHODS
    void controllerStarter();
    void updateStatus();

 //   bool getDebug();
    bool setDebug(bool newDebugStatus);
    bool getSerial();
    bool setSerial(bool newSerialStatus);
 //   bool getPump();
 //   bool setPump(bool newPumpStatus);
 //   LEDstate getLED(byte i);
 //   bool setLED(byte i, LEDstate newLEDstate);
 //   level getWaterLevel();
    
    
  private:
  //MEMBERS                                                                  
    const uint8_t switchPins_[SWITCH_COUNT] = {SWITCH_PINS};
    bool switches_[SWITCH_COUNT];
    const uint8_t LEDpins_[LED_COUNT] = {LED_PINS};
    LEDstate LEDs_[LED_COUNT];

    bool serial_;                           // Guarda si está disponible y habilitado el puerto serial para transmisión de datos. Enviará mensajes.
    bool debug_;                            // Variable que guarda si la depuración de errores está habilitada,
                                            // enviará las funciones que se ejecutan y otros datos críticos.
    bool pumpStatus_;                       // Guarda el estado actual de la bomba de llenado.
    level waterLevel_;                      // Variable de tipo level que guarda el estado actual del nivel de agua en el depósito.                       


  //METHODS
    bool analogGetter(uint8_t pin, byte control, int limit);      // Función que toma lecturas y hace las comparaciones.
    bool digitalGetter(uint8_t pin, byte control);                // Función que toma lecturas y hace las comparaciones,
                                                                  // mismo algoritmo que "analogGetter()", pero en digital.
    void updateWaterLevel();
    void updateSwitches();
    void LEDblink(uint8_t pin);
    void updateLEDs();
    void pumpON();
    void pumpOFF();
    void pumpCore();
};

#endif

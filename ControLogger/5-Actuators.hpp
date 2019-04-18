#ifndef ACTUATORS_H
#define ACTUATORS_H

#include "0-Params.hpp"
#include "2-Serial.hpp"
#include "4-Sensors.hpp"

typedef enum LedState {off = 0, on = 1, blinky = 2} LEDstate;           // Definición de tipos de estado posibles para un LED.

class PumpClass;

class LEDsClass{
  public:
    LEDsClass();
    void init();
    void setLED(int i, LEDstate newLEDstate);
    void updateLEDs(SwitchesClass &Switches, WaterLevelSensor &WaterLS, PumpClass &Pump);

  private:
    const uint8_t LEDpins_[LED_COUNT] = {LED_PINS};
    LEDstate LEDs_[LED_COUNT];
    void LEDblink(uint8_t pin);
};

class PumpClass{
  public:
    PumpClass();
    void init();
    bool getPump() {return pumpStatus_;}
    void pumpON(LEDsClass &LEDs);
    void pumpOFF(LEDsClass &LEDs);

  private:
    bool pumpStatus_;                       // Guarda el estado actual de la bomba de llenado.
};

#endif

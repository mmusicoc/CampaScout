#ifndef SENSORS_H
#define SENSORS_H

#include "0-Params.hpp"
#include "2-Serial.hpp"

typedef enum Level {underMin = 0, midLevel = 1, overMax = 2} level;     // Definición de tipos de estado posibles para el nivel de agua.

class Sensor {
  public:
    Sensor() {}
    virtual void init() = 0;
    int getSensorChecks() {return sensorChecks_;}
    void setSensorChecks(int newChecks);
    int getSensorLimit() {return sensorLimit_;}
    void setSensorLimit(int newLimit);


  protected:
    int sensorChecks_;
    int sensorLimit_;
    bool sensorUpdate(uint8_t pin, byte control, int limit);  // Función que toma lecturas y hace las comparaciones, en modo analógico.
    bool sensorUpdate(uint8_t pin, byte control);             // Función que toma lecturas y hace las comparaciones, en modo digital.
};

class SwitchesClass : public Sensor {
  public:
    SwitchesClass() {}
    void init();
    void updateSwitches();
    bool getSwitch(int switchID) {return switches_[switchID - 1];}

  private:
    const uint8_t switchPins_[SWITCH_COUNT] = {SWITCH_PINS};
    bool switches_[SWITCH_COUNT];
};

class WaterLevelSensor : public Sensor {
  public:
    WaterLevelSensor() {}
    void init();
    void updateWaterLevel();
    level getWaterLevel() {return waterLevel_;}

  private:
    level waterLevel_;                      // Variable de tipo level que guarda el estado actual del nivel de agua en el depósito.
};

#endif

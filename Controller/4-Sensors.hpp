#ifndef SENSORS_H
#define SENSORS_H

#include "0-Params.hpp"
#include "2-Serial.hpp"

typedef enum Level {underMin = 0, midLevel = 1, overMax = 2} level;     // Definição de possíveis tipos de estado para o nível de água.

class Sensor {
  public:
    Sensor() {}
    virtual void init() = 0;
    int getSensorChecks() {return sensorChecks_;}
    void setSensorChecks(int newChecks) {sensorChecks_ = newChecks;}
    int getSensorLimit() {return sensorLimit_;}
    void setSensorLimit(int newLimit) {sensorLimit_ = newLimit;}


  protected:
    int sensorChecks_;
    int sensorLimit_;
    bool sensorUpdate(uint8_t pin, byte control, int limit);  // Função que faz leituras e comparações, em modo analógico.
    bool sensorUpdate(uint8_t pin, byte control);             // FFunção que faz leituras e comparações, em modo digital.
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
    level waterLevel_;                      // Variável do tipo nível que armazena o estado atual do nível de água no tanque.
};

#endif

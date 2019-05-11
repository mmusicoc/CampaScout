#ifndef CONTROLLER_STATUS_H
#define CONTROLLER_STATUS_H

#include "0-Params.hpp"
#include "2-Serial.hpp"
#include "4-Sensors.hpp"
#include "5-Actuators.hpp"

class ControllerCore {
  public:
    ControllerCore() {}
    void init();
    void updateStatus();
    void updateSerial(SerialHandler &USB);

  private:
    SwitchesClass Switches;
    WaterLevelSensor WaterLS;
    LEDsClass LEDs;
    PumpClass Pump;
    void pumpCore();
};

#endif

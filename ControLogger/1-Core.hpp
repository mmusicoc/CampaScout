#ifndef CONTROLLER_STATUS_H
#define CONTROLLER_STATUS_H

#include "0-Params.hpp"
#include "2-Serial.hpp"
#include "3-SDcard.hpp"
#include "4-Sensors.hpp"
#include "5-Actuators.hpp"

class ControllerCore {
  public:
    ControllerCore() {}
    void init();
    void updateStatus(SDcardHandler &SDcard);
    void updateSerial(SerialHandler &USB, SDcardHandler &SDcard);
    float getWaterFlow() {return Flowmeter.getWaterFlow();}

  private:
    SwitchesClass Switches;
    WaterLevelSensor WaterLS;
    FlowmeterClass Flowmeter;
    LEDsClass LEDs;
    PumpClass Pump;
    void pumpCore(SDcardHandler &SDcard);
};

#endif

#include "1-Core.hpp"

using namespace std;

void ControllerCore::init() { // Activación de los pines I/O, definiendo si son de entrada (sensores) o salida (actuadores), e iniciando apagados.
  Switches.init();
  WaterLS.init();
  Flowmeter.init();
  Pump.init();
  LEDs.init();
}

void ControllerCore::updateStatus() {
  Switches.updateSwitches();
  pumpCore();
  LEDs.updateLEDs(Switches, WaterLS, Pump);
}

void ControllerCore::updateSerial(SerialHandler &USB, SDcardHandler &SDcard) {
  static bool openTime = 1;
  int newChecks = USB.getNewChecks();
  int newLimit = USB.getNewLimit();
  int newFlow = USB.getNewFlow();
  if (newChecks != WaterLS.getSensorChecks()){
    Switches.setSensorChecks(newChecks);
    WaterLS.setSensorChecks(newChecks);
    if (!openTime) SDcard.saveParam(newChecks, newLimit, newFlow);
  }
  if (newLimit != WaterLS.getSensorLimit()){
    WaterLS.setSensorLimit(newLimit);
    if (!openTime) SDcard.saveParam(newChecks, newLimit, newFlow);
  }
  if (newFlow != Flowmeter.getFlowRate()){
    Flowmeter.setFlowRate(newFlow);
    if (!openTime) SDcard.saveParam(newChecks, newLimit, newFlow);
  }
  openTime = 0;
}

void ControllerCore::pumpCore() {
  static int coreLoop;                                            // Variables estáticas, cada vez que se ejecuta esta función se mantiene el valor anterior.
  if (coreLoop == CORE_LOOPS) {                                   // Igual que en "checkSwitchMode()" esta rutina se ejecuta sólo cada CORE_LOOP ciclos.
    coreLoop = 0;
    if (Switches.getSwitch(1)){                                   //Modo de control según el botón B1: 1 = Auto; 0 = Manual.
      WaterLS.updateWaterLevel();                                 // Llamada a la función que obtiene el estado del depósito de agua.
      if (WaterLS.getWaterLevel() == underMin && !Pump.getPump()) Pump.pumpON(LEDs);      // Si el depósito está vacío Y la bomba no está ya encendida, la enciende.
      else if (WaterLS.getWaterLevel() == overMax && Pump.getPump()) Pump.pumpOFF(LEDs);  // Si el depósio está lleno Y la bomba no se ha apagado ya, la apaga.
    }
    else if (Switches.getSwitch(2) && !Pump.getPump()) Pump.pumpON(LEDs);   // Si el botón está en  "ENCENDIDO" y la bomba no está ya encendida, la enciende.
    else if (!Switches.getSwitch(2) && Pump.getPump()) Pump.pumpOFF(LEDs);  // Si el botón está en la posición "APAGADO" y la bomba sigue encendida, la apaga.
  }
  else coreLoop++;
}


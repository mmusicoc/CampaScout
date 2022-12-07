#include "1-Core.hpp"

void ControllerCore::init() { // Ativação dos pinos de I/O, definindo se são entrada (sensores) ou saída (atuadores), e iniciando desligamentos.
  Switches.init();
  WaterLS.init();
  Pump.init();
  LEDs.init();
}

void ControllerCore::updateStatus() {
  Switches.updateSwitches();
  pumpCore();
  LEDs.updateLEDs(Switches, WaterLS, Pump);
}

void ControllerCore::updateSerial(SerialHandler &USB) {
  int newChecks = USB.getNewChecks();
  int newLimit = USB.getNewLimit();
  if (newChecks != WaterLS.getSensorChecks()){
    Switches.setSensorChecks(newChecks);
    WaterLS.setSensorChecks(newChecks);
    EEPROM.put(MEM_CHECKS, newChecks);
    Sprint("Sensor checks are now ");
    Serial.println(newChecks);
  }
  if (newLimit != WaterLS.getSensorLimit()){
    WaterLS.setSensorLimit(newLimit);
    EEPROM.put(MEM_LIMIT, newLimit);
    Sprint("Sensibility threshold is now ");
    Serial.println(newLimit);
  }
}

void ControllerCore::pumpCore() {
  static int coreLoop;                                            // Variáveis ​​estáticas, cada vez que esta função é executada, o valor anterior é mantido.
  if (coreLoop == CORE_LOOPS) {                                   // Igual a "checkSwitchMode()" esta rotina é executada apenas a cada ciclo CORE_LOOP.
    coreLoop = 0;
    if (Switches.getSwitch(1)){                                   // Modo de controle de acordo com o botão B1: 1 = Auto; 0 = Manual.
      WaterLS.updateWaterLevel();                                 // Chamada para a função que obtém o estado da caixa d'água.
      if (WaterLS.getWaterLevel() == underMin && !Pump.getPump()) Pump.pumpON(LEDs);      // Se o tanque estiver vazio E a bomba ainda não estiver ligada, ela liga.
      else if (WaterLS.getWaterLevel() == overMax && Pump.getPump()) Pump.pumpOFF(LEDs);  // Se o tanque estiver cheio E a bomba ainda não tiver sido desligada, ela desliga.
    }
    else if (Switches.getSwitch(2) && !Pump.getPump()) Pump.pumpON(LEDs);   // Se o botão estiver "ON" e a bomba ainda não estiver ligada, liga a bomba.
    else if (!Switches.getSwitch(2) && Pump.getPump()) Pump.pumpOFF(LEDs);  // Se o botão estiver na posição "OFF" e a bomba ainda estiver ligada, ele desliga a bomba.
  }
  else coreLoop++;
}

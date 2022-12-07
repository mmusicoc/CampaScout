#include "5-Actuators.hpp"

// LEDs  ******************************************************************************************************************************

void LEDsClass::init(){
  for (int i = 0; i < LED_COUNT; i++) {
    pinMode(LEDpins_[i], OUTPUT);
    digitalWrite(LEDpins_[i], LOW);
  }
}

void LEDsClass::updateLEDs(SwitchesClass &Switches, WaterLevelSensor &WaterLS, PumpClass &Pump) {
  if (Switches.getSwitch(1)) {
    for (byte i = 0; i < 3; i++) {
      digitalWrite(LEDpins_[4], HIGH);
      digitalWrite(LEDpins_[i], i == WaterLS.getWaterLevel());
    }
    if (Pump.getPump()) LEDblink(LEDpins_[3]);
    else digitalWrite(LEDpins_[3], LOW);
  }
  else {
    digitalWrite(LEDpins_[4], LOW);
    if (Switches.getSwitch(2)) digitalWrite(LEDpins_[3], HIGH);
    else digitalWrite(LEDpins_[3], LOW);
  }
}

void LEDsClass::LEDblink(uint8_t LEDpin){
  static unsigned long prevTime = 0;
  unsigned int diff = millis() - prevTime;
  if (diff > LED_BLINK) {
    digitalWrite(LEDpin, !digitalRead(LEDpin));
    prevTime += diff;
  }
}

// BOMBA ******************************************************************************************************************************

void PumpClass::init(){
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW);
}

void PumpClass::pumpON(LEDsClass &LEDs){     // Função de arranque da bomba.
  digitalWrite(RELAY, RELAY_ON);             // Coloca o relé na posição energizada (configurar em Params.hpp)
  pumpStatus_ = true;                        // Salva o novo estado da bomba na variável.
  Sprintln("Pump ON");                       // Se a porta serial estiver habilitada, ela envia uma mensagem informativa.
  LEDs.setLED(4, blinky);
}

void PumpClass::pumpOFF(LEDsClass &LEDs){    // Mesmo algoritmo de "pumON()", mas ao contrário.
  digitalWrite(RELAY, RELAY_OFF);
  pumpStatus_ = false;
  Sprintln("Pump OFF");
  LEDs.setLED(4, off);
}

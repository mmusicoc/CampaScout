#include "5-Actuators.hpp"

using namespace std;

// LEDs CLASS ******************************************************************************************************************************

LEDsClass::LEDsClass(){
  for (byte i = 0; i < LED_COUNT; i++) LEDs_[i] = off;
}

void LEDsClass::init(){
  for (int i = 0; i < LED_COUNT; i++) {
    pinMode(LEDpins_[i], OUTPUT);
    digitalWrite(LEDpins_[i], LOW);
  }
}

void LEDsClass::setLED(int i, LEDstate newLEDstate){
  LEDs_[i - 1] = newLEDstate;
}

void LEDsClass::LEDblink(uint8_t LEDpin){
  static unsigned long prevTime = 0;
  unsigned int diff = millis() - prevTime;
  if (diff > LED_BLINK) {
    digitalWrite(LEDpin, !digitalRead(LEDpin));
    prevTime += diff;
  }
}

void LEDsClass::updateLEDs(SwitchesClass &Switches, WaterLevelSensor &WaterLS, PumpClass &Pump) {
  if (Switches.getSwitch(3)){
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
  else {
    for (byte i = 0; i < LED_COUNT; i++) digitalWrite(LEDpins_[i], LOW);
  }
}

// PUMP CLASS ******************************************************************************************************************************

PumpClass::PumpClass(){
  pumpStatus_ = 0;
}

void PumpClass::init(){
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW);
}

void PumpClass::pumpON(LEDsClass &LEDs){                   // Función de encendido de la bomba.
  digitalWrite(RELAY, RELAY_ON);                           // Pone el relé en la posición de activado (configurar en los #define de la pestaña "Controller".
  pumpStatus_ = true;                                      // Guarda en la variable el nuevo estado de la bomba.
  if(serial) Sprintln("Pump ON");                          // Si el puerto serial está habilitado, envía un mensaje informativo.
  LEDs.setLED(4, blinky);                                  // Enciende el LED del arduino para que veamos físicamente que responde al cambio.
}

void PumpClass::pumpOFF(LEDsClass &LEDs){                  // Mismo algoritmo que "pumON()", pero a la inversa.
  digitalWrite(RELAY, RELAY_OFF);
  pumpStatus_ = false;
  if(serial) Sprintln("Pump OFF");
  LEDs.setLED(4, off);
}


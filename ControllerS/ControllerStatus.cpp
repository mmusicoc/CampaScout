#include "ControllerStatus.hpp"

// **********************************************************************************************************************************************
// PUBLIC ***************************************************************************************************************************************
// **********************************************************************************************************************************************

// INICIALIZACION DE OBJETO STATUS **************************************************************************************************************

ControllerStatus::ControllerStatus() {
  pumpStatus_ = 0;
  waterLevel_ = overMax;
  for (byte i = 0; i < LED_COUNT; i++) LEDs_[i] = off;
}

void ControllerStatus::controllerStarter() {
  FCN
    pinMode(SENSOR_MIN, INPUT);             // Activación de los pines I/O, definiendo si son de entrada (sensores) o salida (actuadores), e iniciando apagados.
  pinMode(SENSOR_MAX, INPUT);
  for (byte i = 0; i < SWITCH_COUNT; i++) {
    pinMode(switchPins_[i], INPUT_PULLUP);  // Para los interruptores, los pines tendrán 2 posibles estados: +5V o flotante,
  }                                         // y para evitar problemas el flotante se fuerza a un estado conocido con el modo INPUT_PULLUP.
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW);
  for (int i = 0; i < LED_COUNT; i++) {
    pinMode(LEDpins_[i], OUTPUT);
    digitalWrite(LEDpins_[i], LOW);
  }
}

// GETTERS & SETTERS ****************************************************************************************************************************
/*
bool ControllerStatus::getDebug() {
  return debug_;
}*/

bool ControllerStatus::setDebug(bool newDebugStatus) {
  if (newDebugStatus == debug_) return 0;
  debug_ = newDebugStatus;
  return 1;
}

bool ControllerStatus::getSerial() {
  return serial_;
}

bool ControllerStatus::setSerial(bool newSerialStatus) {
  if (newSerialStatus == serial_) return 0;
  serial_ = newSerialStatus;
  return 1;
}

// **********************************************************************************************************************************************
// PRIVATE **************************************************************************************************************************************
// **********************************************************************************************************************************************


// PIN GETTERS **********************************************************************************************************************************

bool ControllerStatus::analogGetter(uint8_t pin, byte control, int limit) {      // Función que toma lecturas y hace las comparaciones.
  //FCN
    byte valido = 0;
  for (byte i = 0; i < control; i++) {              // Hace "control" lecturas para asegurarse de que no hay falsas señales.
    if (analogRead(pin) >= limit) valido++;         // Si la señal en "pin" es mayor o igual que "limit", anota la lectura como válida.
    delayMicroseconds(READ_MARGIN);                          // Deja un intervalo de tiempo entre lecturas para que la señal se estabilice.
  }
  if (valido == control) return true;               // Si todas las lecturas han dado el mismo resultado satisfactorio,
  else return false;                                // entonces confirma que la lectura es AFIRMATIVO (sin sentido físico).
}

bool ControllerStatus::digitalGetter(uint8_t pin, byte control) {     // Función que toma lecturas y hace las comparaciones. Mismo algoritmo que "analogGetter()", pero en digital.
  //FCN
    byte i;
  byte valido = 0;
  for (byte i = 0; i < control; i++) {
    if (digitalRead(pin) == HIGH) valido++;         // Si la señal digital es "HIGH", anota la lectura como válida.
    delayMicroseconds(READ_MARGIN);
  }
  if (valido == control) return true;
  else return false;
}

// STATUS UPDATERS ******************************************************************************************************************************

void ControllerStatus::updateStatus() {
  //FCN
  updateSwitches();
  pumpCore();
  updateLEDs();
}

void ControllerStatus::updateWaterLevel() {         // Función que asigna a la variable waterLevel el estado del depósito.
  //FCN
  bool sensorMin = analogGetter(SENSOR_MIN, CONTROL_SENSOR, LIMIT_SENSOR);
  bool sensorMax = analogGetter(SENSOR_MAX, CONTROL_SENSOR, LIMIT_SENSOR);
  if(sensorMax) {
    waterLevel_ = overMax;
    if (serial_) Serial.println("OVER MAX");
  }
  else if(sensorMin) {                              // En caso contrario, si la función "getSensorMin()" da positivo, 
    waterLevel_ = midLevel;                         // el agua está por encima del sensor inferior, pero por debajo del superior: está a media altura.
    if(serial_) Serial.println("MIDDLE LEVEL");
  }
  else {                                            // Si no es ninguno de los casos anteriores, no queda más remedio que el bidón esté vacío y haya que rellenarlo.
    waterLevel_ = underMin;
    if(serial_) Serial.println("UNDER MIN");
  }
}

void ControllerStatus::updateSwitches() {
  //FCN
  static bool switchesPrev[SWITCH_COUNT] = {0,0,0};
  for (byte i = 0; i < SWITCH_COUNT; i++) {
    switchesPrev[i] = switches_[i];
    switches_[i] = !digitalGetter(switchPins_[i], CONTROL_SENSOR);
    if (switchesPrev[i] != switches_[i]){
      Serial.print("Switch B");
      Serial.print(i+1);
      Serial.print(" está ahora en posición ");
      Serial.println(switches_[i]);
    }
  }    
}

void ControllerStatus::LEDblink(uint8_t LEDpin){
  static unsigned long prevTime = 0;
  unsigned int diff = millis() - prevTime;
  if (diff > LED_BLINK) {
    digitalWrite(LEDpin, !digitalRead(LEDpin));
    prevTime += diff;
  }
}

void ControllerStatus::updateLEDs() {
  //FCN
  // WATER LEVEL LEDS
  if (switches_[2]){
    if (switches_[0]) {
      for (byte i = 0; i < 3; i++) {
        digitalWrite(LEDpins_[4], HIGH);
        digitalWrite(LEDpins_[i], i == waterLevel_);
      }
      if (pumpStatus_) LEDblink(LEDpins_[3]);
      else digitalWrite(LEDpins_[3], LOW);
    }
    else {
      digitalWrite(LEDpins_[4], LOW);
      if (switches_[1]) digitalWrite(LEDpins_[3], HIGH);
      else digitalWrite(LEDpins_[3], LOW);
    }
  }
  else {
    for (byte i = 0; i < LED_COUNT; i++) digitalWrite(LEDpins_[i], LOW);
  }
}

void ControllerStatus::pumpON(){                                  // Función de encendido de la bomba.
  FCN
  digitalWrite(RELAY, RELAY_ON);                                  // Pone el relé en la posición de activado (configurar en los #define de la pestaña "Controller".
  pumpStatus_ = true;                                             // Guarda en la variable el nuevo estado de la bomba.
  if(serial_) Serial.println("LOW -> Pump ON");                   // Si el puerto serial está habilitado, envía un mensaje informativo.
  LEDs_[3] = blinky;                                              // Enciende el LED del arduino para que veamos físicamente que responde al cambio.
}

void ControllerStatus::pumpOFF(){                                 // Mismo algoritmo que "pumON()", pero a la inversa.
  FCN
  digitalWrite(RELAY, RELAY_OFF);
  pumpStatus_ = false;
  if(serial_) Serial.println("HIGH -> Pump OFF");
  LEDs_[3] = off;
}

void ControllerStatus::pumpCore() {
  static int coreLoop;                                            // Variables estáticas, cada vez que se ejecuta esta función se mantiene el valor anterior.
  if (coreLoop == CORE_LOOP) {                                    // Igual que en "checkSwitchMode()" esta rutina se ejecuta sólo cada CORE_LOOP ciclos.
    FCN
    coreLoop = 0;
    if (switches_[0]){                                            // Modo de control según el botón B1: 1 = Auto; 0 = Manual.
      updateWaterLevel();                                         // Llamada a la función que obtiene el estado del depósito de agua.
      if (waterLevel_ == underMin && !pumpStatus_) pumpON();      // Si el depósito está vacío Y la bomba no está ya encendida, la enciende.
      else if (waterLevel_ == overMax && pumpStatus_) pumpOFF();  // Si el depósio está lleno Y la bomba no se ha apagado ya, la apaga.
    }
    else if (switches_[1] && !pumpStatus_) pumpON();              // Si el botón está en la posición "ENCENDIDO" y la bomba no está ya encendida, la enciende.
    else if (!switches_[1] && pumpStatus_) pumpOFF();             // Si el botón está en la posición "APAGADO" y la bomba sigue encendida, la apaga.
  }
  else coreLoop++;
}


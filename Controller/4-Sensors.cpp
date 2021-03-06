#include "4-Sensors.hpp"

// SENSOR CLASS **********************************************************************************************************************************

bool Sensor::sensorUpdate(uint8_t pin, byte control, int limit) {
  byte valido = 0;
  for (byte i = 0; i < control; i++) {              // Hace "control" lecturas para asegurarse de que no hay falsas señales.
    if (analogRead(pin) >= limit) valido++;         // Si la señal en "pin" es mayor o igual que "limit", anota la lectura como válida.
    delayMicroseconds(READ_DELAY);                  // Deja un intervalo de tiempo entre lecturas para que la señal se estabilice.
  }
  if (valido == control) return true;               // Si todas las lecturas han dado el mismo resultado satisfactorio,
  else return false;                                // entonces confirma que la lectura es AFIRMATIVO (sin sentido físico).
}

bool Sensor::sensorUpdate(uint8_t pin, byte control) {
  byte valido = 0;
  for (byte i = 0; i < control; i++) {
    if (digitalRead(pin) == HIGH) valido++;         // Si la señal digital es "HIGH", anota la lectura como válida.
    delayMicroseconds(READ_DELAY);
  }
  if (valido == control) return true;
  else return false;
}

// SWITCHES CLASS ******************************************************************************************************************************

void SwitchesClass::init() {
  for (byte i = 0; i < SWITCH_COUNT; i++) pinMode(switchPins_[i], INPUT_PULLUP);
  // Para los interruptores, los pines tendrán 2 posibles estados: +5V o flotante, y éste se fuerza a un estado conocido con el modo INPUT_PULLUP.
}

void SwitchesClass::updateSwitches() {
  static bool switchesPrev[SWITCH_COUNT] = {0, 0};
  for (byte i = 0; i < SWITCH_COUNT; i++) {
    switchesPrev[i] = switches_[i];
    switches_[i] = !sensorUpdate(switchPins_[i], sensorChecks_);
    if (switchesPrev[i] != switches_[i]) {
      Sprint("Switch B");
      Serial.print(i + 1);
      Sprint(" = ");
      Serial.println(switches_[i]);
      if (i == 0 && switches_[i] == 1) Sprintln(">> Auto mode is on");
      else if (i == 0 && switches_[i] == 0) Sprintln(">> Auto mode is off");
    }
  }
}

// WATER LEVEL SENSOR CLASS *******************************************************************************************************************

void WaterLevelSensor::init() {
  pinMode(SENSOR_MIN, INPUT);
  pinMode(SENSOR_MAX, INPUT);
}

void WaterLevelSensor::updateWaterLevel() {         // Función que asigna a la variable waterLevel el estado del depósito.
  bool sensorMin = !sensorUpdate(SENSOR_MIN, sensorChecks_, sensorLimit_);
  bool sensorMax = !sensorUpdate(SENSOR_MAX, sensorChecks_, sensorLimit_);
  level prevLevel = waterLevel_;
  if (sensorMax) {
    waterLevel_ = overMax;
    if (waterLevel_ != prevLevel) Sprintln("OVER MAX");
  } else if (sensorMin) {                           // En caso contrario, si la función "getSensorMin()" da positivo,
    waterLevel_ = midLevel;                         // el agua está por encima del sensor inferior, pero por debajo del superior: está a media altura.
    if (waterLevel_ != prevLevel) Sprintln("MIDDLE LEVEL");
  } else {                                          // Si no es ninguno de los casos anteriores, no queda más remedio que el bidón esté vacío y haya que rellenarlo.
    waterLevel_ = underMin;
    if (waterLevel_ != prevLevel) Sprintln("UNDER MIN");
  }
}

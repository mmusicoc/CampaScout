#include "4-Sensors.hpp"

// CLASSE DO SENSOR **********************************************************************************************************************************

bool Sensor::sensorUpdate(uint8_t pin, byte control, int limit) {
  byte valido = 0;
  for (byte i = 0; i < control; i++) {              // Ele verifica as leituras para garantir que não haja sinais falsos.
    if (analogRead(pin) >= limit) valido++;         // Se o sinal no "pino" for maior ou igual ao "limite", anote a leitura como válida.
    delayMicroseconds(READ_DELAY);                  // Deixa um intervalo de tempo entre as leituras para que o sinal se estabilize.
  }
  if (valido == control) return true;               // Se todas as leituras tiverem dado o mesmo resultado satisfatório.
  else return false;                                // Então confirma que a leitura é AFIRMATIVA (sem significado físico).
}

bool Sensor::sensorUpdate(uint8_t pin, byte control) {
  byte valido = 0;
  for (byte i = 0; i < control; i++) {
    if (digitalRead(pin) == HIGH) valido++;         // Se o sinal digital for "ALTO", anote a leitura como válida.
    delayMicroseconds(READ_DELAY);
  }
  if (valido == control) return true;
  else return false;
}

// CLASSE DOS INTERRUPTORES ******************************************************************************************************************************

void SwitchesClass::init() {
  for (byte i = 0; i < SWITCH_COUNT; i++) pinMode(switchPins_[i], INPUT_PULLUP);
  // Para interruptores, os pinos terão 2 estados possíveis: +5V ou flutuante, e isso é forçado a um estado conhecido com o modo INPUT_PULLUP.
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

// CLASSE DE SENSOR DE NÍVEL DE ÁGUA *******************************************************************************************************************

void WaterLevelSensor::init() {
  pinMode(SENSOR_MIN, INPUT);
  pinMode(SENSOR_MAX, INPUT);
}

void WaterLevelSensor::updateWaterLevel() {         // Função que atribui o estado do tanque à variável waterLevel.
  bool sensorMin = !sensorUpdate(SENSOR_MIN, sensorChecks_, sensorLimit_);
  bool sensorMax = !sensorUpdate(SENSOR_MAX, sensorChecks_, sensorLimit_);
  level prevLevel = waterLevel_;
  if (sensorMax) {
    waterLevel_ = overMax;
    if (waterLevel_ != prevLevel) Sprintln("OVER MAX");
  } else if (sensorMin) {                           // Caso contrário, se a função "getSensorMin()" retornar positivo.
    waterLevel_ = midLevel;                         // A água está acima do sensor inferior, mas abaixo do superior: está na metade.
    if (waterLevel_ != prevLevel) Sprintln("MIDDLE LEVEL");
  } else {                                          // Se não for nenhum dos casos acima, não resta outra opção senão o tambor estar vazio e ele deve ser recarregado.
    waterLevel_ = underMin;
    if (waterLevel_ != prevLevel) Sprintln("UNDER MIN");
  }
}

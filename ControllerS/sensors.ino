// PIN GETTERS **********************************************************************************************************************************

bool analogGetter(uint8_t pin, byte control, int limit){       // Función que toma lecturas y hace las comparaciones.
  byte valido = 0;
  for (byte i = 0; i < control; i++){               // Hace "control" lecturas para asegurarse de que no hay falsas señales.
    if (analogRead(pin) >= limit) valido++;         // Si la señal en "pin" es mayor o igual que "limit", anota la lectura como válida.
    delayMicroseconds(READ_MARGIN);                          // Deja un intervalo de tiempo entre lecturas para que la señal se estabilice.
  }
  if (valido == control) return true;               // Si todas las lecturas han dado el mismo resultado satisfactorio,
  else return false;                                // entonces confirma que la lectura es AFIRMATIVO (sin sentido físico).
}

bool digitalGetter(uint8_t pin, byte control){      // Función que toma lecturas y hace las comparaciones. Mismo algoritmo que "analogGetter()", pero en digital.
  byte i;
  byte valido = 0;
  for (byte i = 0; i < control; i++){
    if (digitalRead(pin) == HIGH) valido++;         // Si la señal digital es "HIGH", anota la lectura como válida.
    delayMicroseconds(READ_MARGIN);
  }
  if (valido == control) return true;
  else return false;
}

// SWITCHES HANDLER ****************************************************************************************************************************

bool checkSwitchMode(){                             // Rutina que lee el estado del interruptor Auto/Manual.
  if(serial) Serial.println();
  FCN                                               // Macro de depuración, devuelve la función en la que estamos (ver pestaña "Debug").
  if (digitalGetter(SWITCH_MODE, 10)) return false; // Si todas las lecturas han sido iguales, el modo es "true" (AUTO).
  return true;
}

bool checkSwitchPump(){                             // Lo mismo que "checkSwitchMode()", pero para el botón de la bomba que se comprueba en modo Manual.
  FCN
  if (digitalGetter(SWITCH_PUMP, 10)) return false;
  return true;
}

// WATER LEVEL SENSOR ****************************************************************************************************************************

bool getSensorMin(){                                // Función que lee el sensor de nivel de agua inferior.
  if (analogGetter(SENSOR_MIN, CONTROL_SENSOR, LIMIT_SENSOR)) return false;     // Si todas las lecturas han dado el mismo resultado satisfactorio,
  else return true;                                 // entonces confirma que el nivel de agua está por DEBAJO del sensor. (así funciona la boya)
}

bool getSensorMax(){                                // Mismo algoritmo que "getSensorMin()", pero para el sensor de nivel de agua superior.
  FCN
  if (analogGetter(SENSOR_MAX, CONTROL_SENSOR, LIMIT_SENSOR)) return false;
  else return true;
}

void getSensors(){                                  // Función que asigna a la variable waterLevel el estado del depósito.
  FCN
  if (getSensorMax()) {                             // Si la función "getSensorMax()" da positivo, el agua está por encima del sensor superior.
    waterLevel = overMax;
    if (serial) Serial.println("OVER MAX");
  }
  else if(getSensorMin()) {                         // En caso contrario, si la función "getSensorMin()" da positivo, 
    waterLevel = midLevel;                          // el agua está por encima del sensor inferior, pero por debajo del superior: está a media altura.
    if(serial) Serial.println("MIDDLE LEVEL");
  }
  else {                                            // Si no es ninguno de los casos anteriores, no queda más remedio que el bidón esté vacío y haya que rellenarlo.
    waterLevel = underMin;
    if(serial) Serial.println("UNDER MIN");
  }
}


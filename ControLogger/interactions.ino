
// SWITCHES HANDLER ****************************************************************************************************************************

bool checkSwitchMode(){                                 // Rutina que lee el estado del interruptor Auto/Manual.
  int valido = 0;
  if(serial) Serial.println();
  FCN                                                   // Macro de depuración, devuelve la función en la que estamos (ver pestaña "Debug").
  for (int i = 0; i < 4; i++) {                         // Comprueba 4 veces que el interruptor está bien pulsado, para evitar falsas lecturas o ruido.
    if (digitalRead(SWITCH_MODE) == HIGH) valido++;
    else valido--;
    delayMicroseconds(20);                              // Entre lecturas hay que dejar una pequeña pausa para que se estabilice la señal.
  }
  if (valido == 4) return true;                         // Si todas las lecturas han sido iguales, guarda el estado en la variable global switchMode.
  return false;
}

bool checkSwitchPump(){                                 // Lo mismo que "checkSwitchMode()", pero para el botón de la bomba que se comprueba en modo Manual.
  FCN
  int valido = 0;
  for (int i = 0; i < 4; i++) {
    if (digitalRead(SWITCH_PUMP) == HIGH) valido++;
    else valido--;
    delayMicroseconds(20);
  }
  if (valido == 4) return true;
  return false;
}


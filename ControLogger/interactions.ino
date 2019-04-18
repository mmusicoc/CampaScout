
// SWITCHES HANDLER ****************************************************************************************************************************

void checkSwitchMode(){                                   // Rutina que lee el estado del interruptor Auto/Manual
  static int checkLoop;
  if (checkLoop == CORE_LOOP) {                           // Sólo va a hacer las lecturas cada vez que pase CORE_LOOP veces por aquí, así consume menos energía
    int valido = 0;
    if(DEB1) Serial.println("");
    FCN
    checkLoop = 0;
    for (int i = 0; i < 4; i++) {                         // Comprueba 4 veces que el interruptor está bien pulsado, para evitar falsas lecturas o ruido
      if (digitalRead(SWITCH_MODE) == HIGH) valido++;
      else valido--;
      delayMicroseconds(20);                              // Entre lecturas hay que dejar una pequeña pausa para que se estabilice la señal
    }
    if (valido == 4) switchMode = true;                   // Si todas las lecturas han sido iguales, guarda el estado en la variable global switchMode
    else if (valido == -4) switchMode = false;
    DEBUG(switchMode)
  }
  else checkLoop++;
}

void checkSwitchPump(){                                   // Lo mismo que "checkSwitchMode()", pero para el botón de la bomba que se comprueba en modo Manual
  FCN
  int valido = 0;
  for (int i = 0; i < 4; i++) {
    if (digitalRead(SWITCH_PUMP) == HIGH) valido++;
    else valido--;
    delayMicroseconds(20);
  }
  if (valido == 4) switchPump = true;
  else if (valido == -4) switchPump = false;
  DEBUG(switchPump)
}


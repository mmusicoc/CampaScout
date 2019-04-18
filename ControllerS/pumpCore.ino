
// PUMP CONTROLLER CORE *******************************************************************************************************************

void controlCore(){                                            
  static int coreLoop;                                            // Variables estáticas, cada vez que se ejecuta esta función se mantiene el valor anterior.
  if (coreLoop == CORE_LOOP) {                                    // Igual que en "checkSwitchMode()" esta rutina se ejecuta sólo cada CORE_LOOP ciclos.
    FCN
    coreLoop = 0;
    if (checkSwitchMode()){                                       // Modo de control según el botón switchMode: 1 = Auto; 0 = Manual.
      getSensors();                                               // Llamada a la función que obtiene el estado del depósito de agua.
      if (waterLevel == underMin && !pumpStatus) pumpON();        // Si el depósito está vacío Y la bomba no está ya encendida, la enciende.
      else if (waterLevel == overMax && pumpStatus) pumpOFF();    // Si el depósio está lleno Y la bomba no se ha apagado ya, la apaga.
    }
    else {                                                        // Modo manual.
      bool switchPump = checkSwitchPump();                        // Controla el estado del botón de encendido manual de la bomba.
      if (switchPump && !pumpStatus) pumpON();                    // Si el botón está en la posición "ENCENDIDO" y la bomba no está ya encendida, la enciende.
      else if (!switchPump && pumpStatus) pumpOFF();              // Si el botón está en la posición "APAGADO" y la bomba sigue encendida, la apaga.
    }
  }
  else coreLoop++;
}

void pumpON(){                                                    // Función de encendido de la bomba.
  FCN
  digitalWrite(RELE, RELAY_ON);                                   // Pone el relé en la posición de activado (configurar en los #define de la pestaña "Controller".
  pumpStatus = true;                                              // Guarda en la variable el nuevo estado de la bomba.
  if(serial) Serial.println("LOW -> Pump ON");                    // Si el puerto serial está habilitado, envía un mensaje informativo.
  digitalWrite(LED, HIGH);                                        // Enciende el LED del arduino para que veamos físicamente que responde al cambio.
}

void pumpOFF(){                                                   // Mismo algoritmo que "pumON()", pero a la inversa.
  FCN
  digitalWrite(RELE, RELAY_OFF);
  pumpStatus = false;
  if(serial) Serial.println("HIGH -> Pump OFF");
  digitalWrite(LED, LOW);
}



// SERIAL PORT ****************************************************************************************************************************

void serialCountdown(int timer){                        // Función que nos visualiza una cuenta atrás del tiempo que queda para enviar un dato y modificarlo
  clearSerial();
  for (int i = timer; i >= 0; i--){                     // Bucle de cuenta atrás
    Serial.print(i);
    Serial.print("  ");
    delay(1000);
    if (Serial.available() > 0) break;                  // Si se ha enviado algo ya, dejar de contar
  }
  Serial.println("\n");
}

void clearSerial(){                                     // Para quitar cualquier dato que hubiera quedado acumulado de un envío anterior inintencionado
  while (Serial.available() > 0) Serial.read();
}

void serialStarter(){                                   // Función que se ejecuta al inicio del todo para comprobar si existe conexión
  Serial.begin(38400);                                  // Activación del puerto
  delay(500);                                           // Pausa para que se establezca la conexión
  serial = Serial;                                      // Si no detecta a nadie escuchando, desactiva el puerto y omite las funciones de serial
  if (serial) Serial.println("Device started\n");       // Envía por USB un mensaje, y luego salta a una nueva línea
  else {
    Serial.end();
    debug = false;
  }
}

void serialParamUpdater(){                              // Función que permite actualizar los parámetros de los sensores
  FCN
  Serial.println("To change parameters, send anything");
  serialCountdown(6);                                   // Nos deja un tiempo para reaccionar
  if (Serial.available() > 0){                          // Si hemos enviado algo, significa que queremos cabiar algún parámetro
    updateLimitMin();                                   // Llama a los sucesivos configuradores de los parámetros
    updateLimitMax();
    updateControlMin();
    updateControlMax();   
  }
  else Serial.println("No param were changed\n\n");     // Si no hemos enviado nada, ignorar
}

void serialDebugUpdater(){                              // Función que permite habilitar la depuración de errores, cambiando la variable debug a verdadero (1)
  FCN
  Serial.println("To enable debugging, send anything");
  serialCountdown(6);
  if(Serial.available() > 0) {                          // Si hemos enviado algo, significa que queremos habilitar la depuración de errores
    debug = true;
    Serial.println("Debugging has been enabled");
  }
  else Serial.println("Debugging remains disabled");    // Si no hemos enviado nada, ignorar.
}

void serialHandler(){                                   // Función que controla todo el proceso de configuración.
  if (serial){                                          // Se ejecuta si "serialStarter()" ha detectado conexión.
    serialParamUpdater();
    serialDebugUpdater();
  }
}

void updateLimitMin(){                                  // Configurador del parámetro "limitMin".
  Serial.println("Set new limitMin");
  Serial.print("Actual value is: ");                    // Primero nos muestra el valor actual, para modificarlo acorde al efecto que queremos resolver.
  Serial.println(limitMin);
  serialCountdown(10);
  if (Serial.available() > 0) {
    limitMin = Serial.parseInt();                       // Guarda en la variable del parámetro el dato que le hemos enviado durante la cuenta atrás.
    DEBUG(limitMin);
    saveLimitMin();                                     // Llama a la función que escribe físicamente el nuevo valor del parámetro en la EEPROM,
  }                                                     // para que la próxima vez que se encienda utilice el valor actualizado en el algoritmo.
  else Serial.println("limitMin change deprecated\n");  // Si no hemos cambiado nada, nos avisa de que ignora este paso.
}

void updateLimitMax(){                                  // Lo mismo que "updateLimitMin()", pero para el parámetro "limitMax".
  Serial.println("Set new limitMax");
  Serial.print("Actual value is: ");
  Serial.println(limitMax);
  serialCountdown(10);
  if (Serial.available() > 0) {
    limitMax = Serial.parseInt();
    saveLimitMax();
  }
  else Serial.println("limitMax change deprecated\n");
}

void updateControlMin(){                                // Lo mismo que "updateLimitMin()", pero para el parámetro "controlMin".
  Serial.println("Set new controlMin");
  Serial.print("Actual value is: ");
  Serial.println(controlMin);
  serialCountdown(10);
  if (Serial.available() > 0) {
    controlMin = Serial.parseInt();
    saveControlMin();
  }
  else Serial.println("controlMin change deprecated\n");
}

void updateControlMax(){                                // Lo mismo que "updateLimitMin()", pero para el parámetro "controlMax".
  Serial.println("Set new controlMax");
  Serial.print("Actual value is: ");
  Serial.println(controlMax);
  serialCountdown(10);
  if (Serial.available() > 0) {
    controlMax = Serial.parseInt();
    saveControlMax();
  }
  else Serial.println("controlMax change deprecated\n");
}


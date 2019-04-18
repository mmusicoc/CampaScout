#include "SerialHandler.hpp"

SerialHandler::SerialHandler(ControllerStatus& Status) {
  Serial.begin(BAUDRATE);                               // Activación del puerto
  delay(500);                                           // Pausa para que se establezca la conexión
  Status.setSerial(Serial);                             // Si no detecta a nadie escuchando, desactiva el puerto y omite las funciones de serial
  if (Status.getSerial()) {
    Serial.println("Device started\n");                 // Envía por USB un mensaje, y luego salta a una nueva línea.
    serialDebugEnabler(Status);
  }
  else {
    Serial.end();
    Status.setDebug(true);
  }
}

void SerialHandler::serialCountdown(int timer) {        // Función que nos visualiza una cuenta atrás del tiempo que queda para enviar un dato y modificarlo
  Serial.read();                                        // Para quitar cualquier dato que hubiera quedado acumulado de un envío anterior inintencionado
  for (int i = timer; i >= 0; i--) {                    // Bucle de cuenta atrás
    Serial.print(i);
    Serial.print("  ");
    delay(1000);
    if (Serial.available() > 0) break;                  // Si se ha enviado algo ya, dejar de contar
  }
  Serial.println("\n");
}

void SerialHandler::serialDebugEnabler(ControllerStatus& Status) { // Función que permite habilitar la depuración de errores, cambiando la variable debug a verdadero (1)
  Serial.println("To enable debugging, send anything");
  serialCountdown(DEBUG_COUNT);
  if (Serial.available() > 0) {                         // Si hemos enviado algo, significa que queremos habilitar la depuración de errores
    Serial.flush();
    Status.setDebug(true);
    Serial.println("Debugging has been enabled");
  }
  else Serial.println("Debugging remains disabled");    // Si no hemos enviado nada, ignorar.
}


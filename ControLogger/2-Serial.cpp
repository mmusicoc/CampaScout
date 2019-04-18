#include "2-Serial.hpp"

using namespace std;

bool serial, debug;

void SerialHandler::init() {
  Serial.begin(BAUDRATE);                               // Activación del puerto
  delay(500);                                           // Pausa para que se establezca la conexión
  serial = Serial;                                      // Si no detecta a nadie escuchando, desactiva el puerto y omite las funciones de serial
  if(serial) Serial.println(F("Device started!"));
}

void SerialHandler::serialWelcome(SDcardHandler &SDcardH){
  SDcardH.loadParam(&newChecks_, &newLimit_, &newFlow_);
  if (serial) {
    Sprintln("Send a command anytime:");
    Sprintln("   DEBUG: enable logging of extra messages");
    Sprintln("   CHECKS: number of signal stability checks");
    Sprintln("   LIMIT: min threshold for sensor validation");
    Sprintln("   FLOW: number of flowmeter pulses per litre");
    serialCountdown(START_COUNT);                       // Nos deja un tiempo para ver los posibles comandos
  } else {
    Serial.end();
    debug = false;
  }
  
}

void SerialHandler::serialCountdown(int timer) {        // Función que nos visualiza una cuenta atrás del tiempo que queda para enviar un dato y modificarlo
  Sprint("\nStarting controller... ");
  Serial.flush();                                       // Para quitar cualquier dato que hubiera quedado acumulado de un envío anterior inintencionado
  for (int i = timer; i >= 1; i--) {                    // Bucle de cuenta atrás
    Serial.print(i);
    Sprint("  ");
    delay(1000);
    if (Serial.available()) break;                      // Si se ha enviado algo ya, dejar de contar
  }
  Sprintln("\n");
}

void SerialHandler::serialWatchDog(){                   // Función que permite actualizar los parámetros de los sensores
  if (Serial.available()){                              // Si hemos enviado algo, significa que queremos cabiar algún parámetro
    String command = Serial.readString();
    Serial.println();
    if (command.equalsIgnoreCase("DEBUG")){
      debug = true;
      Sprintln("Debugging has been enabled");
      return;
    } else if (command.equalsIgnoreCase("CHECKS")) checksUpdater();
    else if (command.equalsIgnoreCase("LIMIT")) limitsUpdater();
    else if (command.equalsIgnoreCase("FLOW")) flowUpdater();
    else Sprintln("Command not available");
  }
}

void SerialHandler::checksUpdater(){
  int tempParam;
  Sprintln("Send number of reads to make valid");
  do {} while (!Serial.available());
  tempParam = Serial.parseInt();
  if (tempParam > 0) newChecks_ = tempParam;
  else Sprintln("Parameter received not valid");
}

void SerialHandler::limitsUpdater(){
  int tempParam;
  Sprintln("Send sensitivity threshold (0,1024)");
  do {} while (!Serial.available());
  tempParam = Serial.parseInt();
  if (tempParam > 0 && tempParam < 1025) newLimit_ = tempParam;
  else Sprintln("Parameter received not valid");
}

void SerialHandler::flowUpdater(){
  int tempParam;
  Sprintln("Send pulses/Litre of flowmeter");
  do {} while (!Serial.available());
  tempParam = Serial.parseInt();
  if (tempParam > 0) newFlow_ = tempParam;
  else Sprintln("Parameter received not valid");
}


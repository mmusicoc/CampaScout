#include "2-Serial.hpp"

void SerialHandler::init() {
  Serial.begin(BAUDRATE);                               // Activación del puerto
  delay(500);                                           // Pausa para que se establezca la conexión                                  
  if(serial_ = Serial) Sprintln("Device started!");     // Si no detecta a nadie escuchando, desactiva el puerto y omite las funciones de serial que más consuman
}

void SerialHandler::serialWelcome(){
  if (serial_) {
    commands();
  } else Serial.end();
  Sprintln("Default parameters were loaded:");
  newChecks_ = DEF_CHECKS;
  newLimit_ = DEF_LIMIT;
}

void SerialHandler::commands(){
  Sprintln("Send a command anytime:");
  Sprintln("   CHECKS: number of signal stability checks");
  Sprintln("   LIMIT: min threshold for sensor validation");
  Sprintln("   FLOW: number of flowmeter pulses per litre");
}

void SerialHandler::serialWatchDog(){   // Función que permite actualizar los parámetros de los sensores
  if (Serial.available()){                              // Si hemos enviado algo, significa que queremos cabiar algún parámetro
    String command = Serial.readString();
    Sprint("\n");
    if (command.equals("checks")) updateChecks();
    else if (command.equals("limit")) updateLimits();
    else {
      Sprint("Error, command \"");
      Serial.print(command);
      Sprintln("\" not available!");
      commands();
    }
  }
}

void SerialHandler::updateChecks(){
  int tempParam;
  Sprintln("Send number of reads to make valid");
  do {} while (!Serial.available());
  tempParam = Serial.parseInt();
  if (tempParam > 0) newChecks_ = tempParam;
  else Sprintln("Parameter received not valid, update aborted");
}

void SerialHandler::updateLimits(){
  int tempParam;
  Sprintln("Send sensitivity threshold (0,1024)");
  do {} while (!Serial.available());
  tempParam = Serial.parseInt();
  if (tempParam > 0 && tempParam < 1025) newLimit_ = tempParam;
  else Sprintln("Parameter received not valid, update aborted");
}

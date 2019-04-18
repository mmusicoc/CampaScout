#include "2-Serial.hpp"

void SerialHandler::init() {
  Serial.begin(BAUDRATE);                               // Activación del puerto
  delay(500);                                           // Pausa para que se establezca la conexión                                  
  if(serial_ = Serial) Sprintln("Device started!");     // Si no detecta a nadie escuchando, desactiva el puerto y omite las funciones de serial que más consuman
}

void SerialHandler::serialWelcome(SDcardHandler &SDcard){
  if (serial_) {
    commands(SDcard);
    if(SDcard.available()) SDcard.loadParam(&newChecks_, &newLimit_, &newFlow_);
  } else Serial.end();
  if (!SDcard.available()){
    Sprintln("Default parameters were loaded:");
    newChecks_ = DEF_CHECKS;
    newLimit_ = DEF_LIMIT;
    newFlow_ = DEF_FLOW;
    SDcard.updateLogFreq(DEF_FREQ);
  }
}

void SerialHandler::commands(SDcardHandler &SDcard){
  Sprintln("Send a command anytime:");
  Sprintln("   CHECKS: number of signal stability checks");
  Sprintln("   LIMIT: min threshold for sensor validation");
  Sprintln("   FLOW: number of flowmeter pulses per litre");
  if(SDcard.available()) {
    Sprintln("   LOG: shows contents of log file");
    Sprintln("   LOGFREQ: period between logging entries");
    Sprintln("   RESET: empty logging file to restart count");
    }
}

void SerialHandler::serialWatchDog(SDcardHandler &SDcard){   // Función que permite actualizar los parámetros de los sensores
  if (Serial.available()){                              // Si hemos enviado algo, significa que queremos cabiar algún parámetro
    String command = Serial.readString();
    Serial.println();
    if (command.equalsIgnoreCase("CHECKS")) updateChecks();
    else if (command.equalsIgnoreCase("LIMIT")) updateLimits();
    else if (command.equalsIgnoreCase("FLOW")) updateFlow();
    else if (command.equalsIgnoreCase("LOG") && SDcard.available()) SDcard.read();
    else if (command.equalsIgnoreCase("LOGFREQ") && SDcard.available()) updateFreq(SDcard);
    else if (command.equalsIgnoreCase("RESET") && SDcard.available())resetLog(SDcard);
    else {
      Sprint("Error, command \"");
      Serial.print(command);
      Sprintln("\" not available!");
      commands(SDcard);
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

void SerialHandler::updateFlow(){
  int tempParam;
  Sprintln("Send pulses/Litre of flowmeter");
  do {} while (!Serial.available());
  tempParam = Serial.parseInt();
  if (tempParam > 0) newFlow_ = tempParam;
  else Sprintln("Parameter received not valid, update aborted");
}

void SerialHandler::updateFreq(SDcardHandler &SDcard){
  int tempParam;
  Sprintln("Send logging period (seconds between entries)");
  do {} while (!Serial.available());
  tempParam = Serial.parseInt();
  if (tempParam > 0) {
    SDcard.updateLogFreq(tempParam);
    SDcard.saveParam(newChecks_, newLimit_, newFlow_);
  }
  else Sprintln("Parameter received not valid, update aborted");
}


void SerialHandler::resetLog(SDcardHandler &SDcard){
  String command;
  Sprintln("Are you sure you want to erase all previous data");
  Sprint("in SDcard/");
  Sprint(LOGFILE);
  Sprintln(" ?  (yes/no)");
  do {} while (!Serial.available());
  command = Serial.readString();
  if (command.equalsIgnoreCase("YES")) SDcard.resetLogFile();
  else Sprintln("You did not confirm, reset log file aborted");
}


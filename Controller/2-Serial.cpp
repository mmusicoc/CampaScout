#include "2-Serial.hpp"

void SerialHandler::init() {
  Serial.begin(BAUDRATE);                               // Ativação da porta
  delay(500);                                           // Pausa para conexão ser estabelecida                                  
  if(serial_ = Serial) Sprintln("Device started!");     // Se não detectar nenhum barulho, desabilita a porta e pula as funções seriais que consomem mais
}

void SerialHandler::serialWelcome(){
  if (serial_) {
    commands();
  } else Serial.end();
  Sprintln("Default parameters were loaded:");
  EEPROM.get(MEM_CHECKS, newChecks_);
  EEPROM.get(MEM_LIMIT, newLimit_);
}

void SerialHandler::commands(){
  Sprintln("Send a command anytime:");
  Sprintln("   checks: number of signal stability checks");
  Sprintln("   limit: min threshold for sensor validation");
}

void SerialHandler::serialWatchDog(){   // Função que permite atualizar os parâmetros dos sensores
  if (Serial.available()){                              // Se enviamos algo, significa que queremos alterar algum parâmetro
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

#ifndef SERIAL_HANDLER_H
#define SERIAL_HANDLER_H

#include <EEPROM.h>
#include "0-Params.hpp"

class SerialHandler {
  public:
    SerialHandler() {}
    void init();
    bool available() {return serial_;}    // Salva a porta serial para transmissão de dados. Se estiver disponível e habilitada, ele enviará mensagens.
    void serialWelcome();
    void serialWatchDog();
    int getNewChecks() {return newChecks_;}
    int getNewLimit() {return newLimit_;}

  private:
    bool serial_;
    int newChecks_;
    int newLimit_;
    void commands();
    void updateChecks();
    void updateLimits();
};

#endif

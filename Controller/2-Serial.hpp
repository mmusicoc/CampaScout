#ifndef SERIAL_HANDLER_H
#define SERIAL_HANDLER_H

#include "0-Params.hpp"

class SerialHandler {
  public:
    SerialHandler() {}
    void init();
    bool available() {return serial_;}    // Guarda si está disponible y habilitado el puerto serial para transmisión de datos. Enviará mensajes.
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

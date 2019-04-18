#ifndef SERIAL_HANDLER_H
#define SERIAL_HANDLER_H

#include "0-Params.hpp"
#include "3-SDcard.hpp"

extern bool serial;                       // Guarda si está disponible y habilitado el puerto serial para transmisión de datos. Enviará mensajes.
extern bool debug;                        // Guarda si la depuración de errores está habilitada, enviará las funciones que se ejecutan y otros datos críticos.

class SerialHandler {
  public:
    SerialHandler() {}
    void init();
    void serialWelcome(SDcardHandler &SDcardH);
    void serialWatchDog();
    int getNewChecks() {return newChecks_;}
    int getNewLimit() {return newLimit_;}
    int getNewFlow() {return newFlow_;}

  private:
    int newChecks_;
    int newLimit_;
    int newFlow_;
    void serialCountdown(int timer);
    void checksUpdater();
    void limitsUpdater();
    void flowUpdater();
};

#endif

#ifndef SERIAL_HANDLER_H
#define SERIAL_HANDLER_H

#include "0-Params.hpp"
#include "3-SDcard.hpp"

class SerialHandler {
  public:
    SerialHandler() {}
    void init();
    bool available() {return serial_;}    // Guarda si está disponible y habilitado el puerto serial para transmisión de datos. Enviará mensajes.
    void serialWelcome(SDcardHandler &SDcard);
    void serialWatchDog(SDcardHandler &SDcard);
    int getNewChecks() {return newChecks_;}
    int getNewLimit() {return newLimit_;}
    int getNewFlow() {return newFlow_;}

  private:
    bool serial_;
    int newChecks_;
    int newLimit_;
    int newFlow_;
    void commands(SDcardHandler &SDcard);
    void serialCountdown(int timer);
    void updateChecks();
    void updateLimits();
    void updateFlow();
    void updateFreq(SDcardHandler &SDcard);
    void resetLog(SDcardHandler &SDcard);
};

#endif

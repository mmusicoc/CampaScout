#ifndef SD_CARD_HANDLER_H
#define SD_CARD_HANDLER_H

#include "0-Params.hpp"
#include <EEPROM.h>

class EEPROMHandler {
  public:
    EEPROMHandler();
    void init();
    void loadParam(int* checks, int* limit);
    void saveParam(int checks, int limit);
    void read();
    void printEvent();

  private:
  
};

#endif

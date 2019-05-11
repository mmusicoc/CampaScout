#ifndef SD_CARD_HANDLER_H
#define SD_CARD_HANDLER_H

#include "0-Params.hpp"
#include <EEPROM.h>



class EEPROMhandler {
  public:
    EEPROMhandler(){};
    void loadParam(int* checks, int* limit);
    void saveChecks(int checks);
    void saveLimit(int limit);
};

#endif

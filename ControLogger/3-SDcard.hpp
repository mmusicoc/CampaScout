#ifndef SD_CARD_HANDLER_H
#define SD_CARD_HANDLER_H

#include "0-Params.hpp"


#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include "RTClib.h"           // Not default, download and install in Arduino IDE, available on SD card

class SDcardHandler {
  public:
    SDcardHandler();
    void init();
    void loadParam(int* checks, int* limit, int* flow);
    void saveParam(int checks, int limit, int flow);

  private:
    File paramFile_, logFile_;
    RTC_DS1307 rtc_;
    DateTime currentTime_;
};

#endif

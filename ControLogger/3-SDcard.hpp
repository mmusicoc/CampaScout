#ifndef SD_CARD_HANDLER_H
#define SD_CARD_HANDLER_H

#include "0-Params.hpp"

#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include "RTClib.h"           // Not default, download and install in Arduino IDE, available on SD card

typedef enum eventType {none = 0, pumpOn = 1, pumpOff = 2} Event;

class RTChandler {
  public:
    RTChandler() {}
    void init();
    bool available() {return (bool)RTCactive_;}
    void event();
    bool timer();
    String fullTime();
    int getFreq() {return freq_;}
    void setFreq(int newFreq);
  private:
    int freq_;
    RTC_DS3231 rtc_;
    bool RTCactive_;
    DateTime prevTime_;
    DateTime currentTime_;
    char weekDay_[7] = {'D', 'L', 'M', 'X', 'J', 'V', 'S'};
};

class SDcardHandler {
  public:
    SDcardHandler();
    void init();
    void event(Event action);
    bool available() {return card_;}
    void loadParam(int* checks, int* limit, int* flow);
    void saveParam(int checks, int limit, int flow);
    void read();
    void updateLogFreq(int newFreq) {RTClock.setFreq(newFreq);}
    void resetLogFile();
    void printEvent();
    void logSD(float lastWaterFlow);

  private:
    bool card_;
    Event event_;
    bool state_;
    float acumWaterFlow_;
    File paramFile_;
    File logFile_;
    RTChandler RTClock;
};

#endif

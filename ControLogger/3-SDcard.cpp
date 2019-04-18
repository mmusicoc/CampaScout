#include "3-SDcard.hpp"

// RTC CLOCK HANDLER CLASS ****************************************************************************************************************

void RTChandler::init(){
  Wire.begin();
  if (!rtc_.begin()){
    Sprintln("Couldn't find RTC");
    RTCactive_ = false;
  } else {
    if(RESET_RTClock) rtc_.adjust(DateTime(F(__DATE__), F(__TIME__)));
    prevTime_ = rtc_.now();
    RTCactive_ = true;
  }
}

void RTChandler::event(){
  prevTime_ = currentTime_;
  currentTime_ = rtc_.now();
}

bool RTChandler::timer(){
  static int timerLoop = 0;
  if (timerLoop % TIMER_SEC == 0){
    currentTime_ = rtc_.now();
    if (currentTime_.unixtime() - prevTime_.unixtime() >= freq_){
      return true;
    }
  }
  timerLoop++;
  return false;
}

String RTChandler::fullTime(){
  char dateTime[24];
  sprintf(dateTime, "%.2d/%.2d/%d\t%.2d:%.2d:%.2d", currentTime_.day(), currentTime_.month(), currentTime_.year(), currentTime_.hour(), currentTime_.minute(), currentTime_.second());
  return dateTime;
}

void RTChandler::setFreq(int newFreq){
   freq_ = newFreq;
   Sprint("\nTime space between log entries is now ");
  Serial.println(freq_);

}

// SD CARD HANDLER CLASS ******************************************************************************************************************

SDcardHandler::SDcardHandler() {
  event_ = none;
  state_ = false;
  acumWaterFlow_ = 0.0;
}

void SDcardHandler::init(){
  card_ = SD.begin(CHIP_SELECT);
  if (!card_) {
    Sprintln("SD card failed");
  } else {
    Sprintln("SD card ok");
    RTClock.init();
  }
}

void SDcardHandler::event(Event action){
  if(action >= 0 && action <= 2) {
    event_ = action;
    if (action == pumpOn) state_ = true;
    if (action == pumpOff) state_ = false;
  }
}

void SDcardHandler::loadParam(int* checks, int* limit, int* flow){
  if (!(paramFile_ = SD.open(PARAMFILE))) {
    Sprintln("File error to read");
  } else {
    Sprint("\nParameters loaded from SDcard/");
    Sprint(PARAMFILE);
    paramFile_.readStringUntil('\n');
    *checks= paramFile_.parseInt();
    paramFile_.readStringUntil(' ');
    *limit = paramFile_.parseInt();
    paramFile_.readStringUntil(' ');
    *flow = paramFile_.parseInt();
    paramFile_.readStringUntil(' ');
    RTClock.setFreq(paramFile_.parseInt());
    paramFile_.close();
  }
}

void SDcardHandler::saveParam(int checks, int limit, int flow){
  SD.remove(PARAMFILE);
  if (!(paramFile_ = SD.open(PARAMFILE, FILE_WRITE))) {
    Sprintln("File error to write");
  } else {
    paramFile_.println(F("Checks, Limit, Flow, LogFreq"));
    paramFile_.print(checks);
    paramFile_.print(F(", "));
    paramFile_.print(limit);
    paramFile_.print(F(", "));
    paramFile_.println(flow);
    paramFile_.print(F(", "));
    paramFile_.println(RTClock.getFreq());
    paramFile_.close();
    Sprint("New parameters saved on SDcard/");
    Sprintln(PARAMFILE);
  }
}

void SDcardHandler::read(){
  if (!(logFile_ = SD.open(LOGFILE, FILE_READ))) {
    Sprintln("File error to read");
  } else {
    Sprint("Contents of SDcard/");
    Sprintln(LOGFILE);
    while(logFile_.available()) Serial.write(logFile_.read());
    Sprint("End of file SDcard/");
    Sprintln(LOGFILE);
    Sprint("\n");
    logFile_.close();
  }
}

void SDcardHandler::resetLogFile(){
  SD.remove(LOGFILE);
  if (!(logFile_ = SD.open(LOGFILE, FILE_WRITE))) {
    Sprintln("File error to write");
  } else {
    logFile_.println(F("Full date\tTimestamp\tEvent   \tWater since previous log entry"));
    logFile_.close();
    Sprint("New logging file created as SDcard/");
    Sprintln(LOGFILE);
    Serial.println();
  }
}

void SDcardHandler::printEvent(){
  logFile_.print(RTClock.fullTime());
  logFile_.print(F("\t"));
  switch (event_){
    case none: {
      logFile_.print(F("Periodic"));
      break;
    }
    case pumpOn: {
      logFile_.print(F("Pump ON "));
      break;
    }
    case pumpOff: {
      logFile_.print(F("Pump OFF"));
      break;
    }
  }
  logFile_.print(F("\t"));
  logFile_.print(acumWaterFlow_, 2);
  logFile_.println();
}

void SDcardHandler::logSD(float lastWaterFlow){
  static bool start = true;
  acumWaterFlow_ += lastWaterFlow;
  if (event_ || ((RTClock.available() ? RTClock.timer() : 0) && state_ == true)){
    RTClock.event();
    if (!(logFile_ = SD.open(LOGFILE, FILE_WRITE))) {
      if (start) Sprintln("File error to write");
    } else {
      if (start){
        Sprint("\nSDcard/");
        Sprint(LOGFILE);
        Sprintln("  succesfully opened, logging started\n");
      }
      printEvent();
      acumWaterFlow_ = 0.0;
      logFile_.close();
      Sprint("New log saved on SDcard/");
      Sprintln(LOGFILE);
    }
    event_ = none;
    start = false;
  }
}


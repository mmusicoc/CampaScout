#include "3-SDcard.hpp"

SDcardHandler::SDcardHandler() {
  
}

void SDcardHandler::init(){
  if (!SD.begin(CHIP_SELECT)) {
    Sprintln("SD card failed");
    while (1);
  }
  Sprintln("SD card ok");
 // logFile_ = SD.open(LOGFILE, FILE_WRITE);
//  Wire.begin();
//  rtc_.begin();
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Uncomment in order to reset RTC module to compile time
  //rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));     // Uncomment in order to reset RTC module to specific time
}

void SDcardHandler::loadParam(int* checks, int* limit, int* flow){
  if (!(paramFile_ = SD.open(PARAMFILE))) {
    Sprintln("File error to read.");
  } else {
    paramFile_.readStringUntil('\n');
    *checks= paramFile_.parseInt();
    paramFile_.readStringUntil(' ');
    *limit = paramFile_.parseInt();
    paramFile_.readStringUntil(' ');
    *flow = paramFile_.parseInt();
    paramFile_.close();
  }
}

void SDcardHandler::saveParam(int checks, int limit, int flow){
  SD.remove(PARAMFILE);
  if (!(paramFile_ = SD.open(PARAMFILE, FILE_WRITE))) {
    Sprintln("File error to write");
  } else {
    paramFile_.println("CHECKS, LIMIT, FLOW");
    paramFile_.print(checks);
    paramFile_.print(", ");
    paramFile_.print(limit);
    paramFile_.print(", ");
    paramFile_.println(flow);
    paramFile_.close();
    Sprint("New parameters saved on SDcard/");
    Sprintln(PARAMFILE);
  }
}

void SDcardHandler


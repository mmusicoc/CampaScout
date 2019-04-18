
const int chipSelect = 4;
#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 rtc;


//The SDlibrary needs SPI
#include <SPI.h>
#include "SD.h"
//Some SD Card code borrowed from Adafruit library examples
// set up variables using the SD utility library functions:

File dataFile;
#define LOGFILE "datalog.txt"

void setup() {
  Serial.begin(9600); 
  //Initialize the Sensor
    
  Serial.println("Starting SDCard reader and card");
  pinMode(chipSelect, OUTPUT);
  pinMode(SS, OUTPUT);
  
  if (!SD.begin(chipSelect)) {
    Serial.println("SD Card initialization failed!");
    return;
  }
  
  Serial.println("Opening logfile for write.");
  dataFile = SD.open(LOGFILE, FILE_WRITE);
  if (! dataFile) {
    Serial.println("error opening log file");
    while (1) ;
  }
  
  
  Serial.println("Starting Real Time Clock");
  Wire.begin();

  rtc.begin();
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));  //uncomment this once and upload. Then comment it out and upload again
  //This will set the time the first time you upload it and if you don't upload again with it commented out it will 
  //reset the clock to the time the code was compliled each time.
  
  if (! rtc.isrunning()) {  //code borrowed from adafruit example rtc code
    Serial.println("RTC is NOT running!");
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  DateTime now = rtc.now();
  Serial.print("Unixtime: ");
  Serial.println(now.unixtime());
}

void loop(){
  char msg[13];
  sprintf(msg,"Hola soy Mario");
  logThis(msg);  
  delay(3000); 
}


void logThis(char* logmessage){
  char message[120];
  DateTime now = rtc.now();
  long epoch = now.unixtime();
  int Year = now.year();
  int Month = now.month();
  int Day = now.day();
  int Hour = now.hour();
  int Minute = now.minute();
  int Second = now.second();
  sprintf(message, "%ld,%d/%d/%d %02d:%02d:%02d,%s",epoch,Year,Month,Day,Hour,Minute,Second,logmessage );
  //Write the entry to the log file and console
  dataFile.println(message);
  dataFile.flush();
  // print to the serial port too:
  Serial.println(message);
}



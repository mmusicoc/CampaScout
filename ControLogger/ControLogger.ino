#include <arduino.h>
#include "EEPROM.h"

//PIN IDs
#define SENSOR_5V A5
#define SENSOR_MIN A4
#define SENSOR_MAX A3
#define RELE A7

//EEPROM PATHS
#define MEM_DATE 0                                  //int
#define MEM_TOTALLITRES sizeof(int)                 //float
#define MEM_FLOW MEM_TOTALLITRES + sizeof(float)    //float
#define MEM_LIMIT_MIN MEM_FLOW + sizeof (float)     //int
#define MEM_LIMIT_MAX MEM_LIMIT_MIN + sizeof (int)  //int
#define MEM_DAILYRUNTIME MEM_LIMIT_MAX + sizeof(int)//unsigned long
#define MEM_DAILYCOUNTER MEM_DAILYRUNTIME + sizeof(unsigned long) - sizeof(struct day) + sizeof(struct day) * 

//PARAMETERS 36000000
#define CONFIGURE_TIMEOUT 15000
#define MIN_DAILYRUNTIME 36000000
#define SAVE_LOOP 500000
#define DEBUG_LOOP 2000
#define CONTROL 10

struct day{
  unsigned long activeTime;
  float litres;
};
bool pumpStatus, underMin, overMax, midLevel;
int date, aproxTotalLitres, limitMin, limitMax;
unsigned long lastActiveTime, actualActiveTime;
unsigned long dailyRuntime, lastRuntime, actualRuntime;
unsigned long saveLoopCounter, debugLoopCounter;
float flow, totalLitres;
struct day today;

void saveData(){
  EEPROM.put(MEM_TOTALLITRES, totalLitres/1000);
  EEPROM.put(MEM_DAILYRUNTIME, dailyRuntime);
  EEPROM.put(MEM_DAILYCOUNTER date, today);
  Serial.println("\n***************************");
  Serial.print("RT: ");
  Serial.print(dailyRuntime/3600000);
  Serial.print("h");
  Serial.print((dailyRuntime%3600000)/60000);
  Serial.print("min\tON: ");
  Serial.print(today.activeTime/3600000);
  Serial.print("h");
  Serial.print((today.activeTime%3600000)/60000);
  Serial.print("min\tUsed: ");
  Serial.print(today.litres);
  Serial.println(" L");
  Serial.println("***************************");
}

// *************************************************** SOLO INICIO ***************************************************************

void loadData(){
  EEPROM.get(MEM_DATE, date);
  EEPROM.get(MEM_TOTALLITRES, totalLitres);
  EEPROM.get(MEM_FLOW, flow);
  EEPROM.get(MEM_LIMIT_MIN, limitMin);
  EEPROM.get(MEM_LIMIT_MAX, limitMax);
  EEPROM.get(MEM_DAILYRUNTIME, dailyRuntime);
  delayMicroseconds(100);
  Serial.println("Data loaded");
  if (dailyRuntime > MIN_DAILYRUNTIME){
    date++;
    EEPROM.put(MEM_DATE, date);
    dailyRuntime=0;
    today.activeTime=0;
    today.litres=0;
    saveData();
    delayMicroseconds(100);
    Serial.println("New day started");
  }
  else {
    EEPROM.get(MEM_DAILYCOUNTER date, today);
    delayMicroseconds(100);
    Serial.println("Still in previous date");
  }
}

void showData(){
  int i;
  struct day show;
  aproxTotalLitres=(int)totalLitres;
  delayMicroseconds(100);
  Serial.print("Total saved days: ");
  Serial.println(date);
  delayMicroseconds(100);
  Serial.print("Total consumed water: ");
  Serial.println(aproxTotalLitres);
  delayMicroseconds(100);
  Serial.print("Saved average flow: ");
  Serial.println(flow);
  delayMicroseconds(100);
  Serial.print("Saved conductivities: MIN ");
  Serial.print(limitMin);
  Serial.print(", MAX ");
  Serial.println(limitMax);
  delayMicroseconds(100);
  Serial.print("Actual daily runtime: ");
  Serial.print(dailyRuntime/3600000);
  Serial.print("h");
  Serial.print((dailyRuntime%3600000)/60000);
  Serial.println("min");
  delayMicroseconds(100);
  Serial.println("\n***************************");
  Serial.println("Daily activity:");
  Serial.println("***************************\n");
  for(i=1; i<=date; i++){
    EEPROM.get(MEM_DAILYCOUNTER i, show);
    delayMicroseconds(100);
    Serial.print("Day ");
    Serial.print(i);
    delayMicroseconds(100);
    Serial.print(",\tActive time: ");
    Serial.print(show.activeTime/3600000);
    Serial.print("h");
    Serial.print((show.activeTime%3600000)/60000);
    Serial.print("min\tWater consumption: ");
    delayMicroseconds(100);
    Serial.print(show.litres);
    Serial.println(" L");
  }
  delayMicroseconds(100);
  Serial.println("\n***************************\n");
  lastRuntime=millis();
  Serial.print("Counter is running on day ");
  Serial.println(date);
}

void resetCounter(){
  date=1;
  dailyRuntime=0;
  totalLitres=0;
  today.activeTime=0;
  today.litres=0;
  EEPROM.put(MEM_DATE, date);
  EEPROM.put(MEM_DAILYRUNTIME, dailyRuntime);
  EEPROM.put(MEM_TOTALLITRES, totalLitres);
  Serial.print("Database was reset except flow variable, which is ");
  Serial.println(flow);
}

void updateFlow(){
  flow = Serial.parseFloat();
  EEPROM.put(MEM_FLOW, flow);
  Serial.print("Water flow has been updated to ");
  Serial.println(flow);
}

void updateConductivity(){
  limitMin = Serial.parseFloat();
  limitMax = Serial.parseFloat();
  EEPROM.put(MEM_LIMIT_MIN, limitMin);
  EEPROM.put(MEM_LIMIT_MAX, limitMax);
  Serial.print("Water conductivities have been updated to: MIN ");
  Serial.print(limitMin);
  Serial.print(", MAX ");
  Serial.print(limitMax);
}

void serialUpdate(){
  String command;
  int configDelay=0;
  showData();
  Serial.println("Available configuration commands:");
  Serial.println("\"RESET 0\" erases all counters, setting day as 1");
  Serial.println("\"FLOW [L/min, decimals admitted]\" enables water flow update");
  Serial.println("\"COND [MIN] [MAX]\" enables water conductivity update");
  do{
    Serial.setTimeout(CONFIGURE_TIMEOUT/10.0);
    command = Serial.readStringUntil(' ');
    configDelay++;
  } while (command.equalsIgnoreCase("") && configDelay < 10);
  if (command.equalsIgnoreCase("RESET")) resetCounter();
  else if (command.equalsIgnoreCase("FLOW")) updateFlow();
  else if (command.equalsIgnoreCase("COND")) updateConductivity();
  else Serial.println("Nothing was changed. Counter is initializing...");
  Serial.print("\n");
}

// *************************************************** SOLO RUNTIME **************************************************************

bool getSensorMin(){
  int i;
  int valido=0;
  int measure = analogRead(SENSOR_MAX);
  for (i=0; i<CONTROL; i++){
    if (measure<=limitMin)valido++;
    delayMicroseconds(50);
  }
  if (valido==CONTROL) return 1;
  else return 0;
}

bool getSensorMax(){
  int i;
  int valido=0;
  int measure = analogRead(SENSOR_MAX);
  for (i=0; i<CONTROL; i++){
    if (measure>=limitMax)valido++;
    delayMicroseconds(50);
  }
  if (valido==CONTROL) return 1;
  else return 0;
}

void getSensors(){
  if (getSensorMin()){
    if (getSensorMax()) {
      overMax = true;
      midLevel = false;
      underMin = false;
    }
    else{
      overMax = false;
      midLevel = true;
      underMin = false;
    }
  } else{
    overMax = false;
    midLevel = false;
    underMin = true;
  }
}

void updateData(){
  actualRuntime = millis();
  if (pumpStatus){
    actualActiveTime = actualRuntime;
    today.activeTime+=(actualActiveTime-lastActiveTime);
    today.litres+=(actualActiveTime-lastActiveTime)*flow/60000;
    totalLitres+=(actualActiveTime-lastActiveTime)*flow/60000;
    lastActiveTime=actualActiveTime;
  }
  else lastActiveTime = actualRuntime;
  dailyRuntime+=(actualRuntime-lastRuntime);
  lastRuntime=actualRuntime;
  if(!(saveLoopCounter%SAVE_LOOP))saveData();
  saveLoopCounter++;
}

void pumpON(){
  digitalWrite(RELE, LOW);
  pumpStatus=true;
  Serial.println("\nPump switched ON\n");
}

void pumpOFF(){
  digitalWrite(RELE, HIGH);
  pumpStatus=false;
  Serial.println("\nPump switched OFF\n");
  //saveData();
}

void automatic(){
  getSensors();
  if (underMin && !pumpStatus) pumpON();
  else if (overMax && pumpStatus) pumpOFF();
  
}

void serialDebug(){
  if (!(debugLoopCounter%DEBUG_LOOP)){
    if (pumpStatus) Serial.print("Pump: ON");
    else Serial.print("Pump: OFF");
    if(overMax) Serial.print("\tFULL");
    else if (midLevel) Serial.print("\tMID LEVEL");
    else Serial.print("\tUNDER MIN");
    Serial.print("\t");
    Serial.print(analogRead(SENSOR_MIN));
    Serial.print("\t");
    Serial.println(analogRead(SENSOR_MAX));
  }
  debugLoopCounter++;
}

// *************************************************** SETUP *********************************************************************

void setup() {
  Serial.begin(38400);
  pinMode(SENSOR_MIN, INPUT);
  pinMode(SENSOR_MAX, INPUT);
  pinMode(SENSOR_5V, OUTPUT);
  pinMode(RELE, OUTPUT);

  digitalWrite(SENSOR_5V, HIGH);
  digitalWrite(RELE, HIGH);
  
  delay(1500);
  Serial.println("Device started");
  loadData();
  serialUpdate();
  pumpStatus = true;
  saveLoopCounter=0;
  debugLoopCounter=0;
  updateData();
}

// *************************************************** LOOP **********************************************************************

void loop() {
  //automatic();
 // updateData();
  //serialDebug();
  Serial.println(analogRead(SENSOR_MIN));
}

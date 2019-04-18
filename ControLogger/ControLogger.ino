#include <arduino.h>
#include "EEPROM.h"

//PIN IDs
#define SENSOR A7
#define RELE 3
#define RELE_5V 2
#define SWITCH_5V 4
#define SWITCH 5

//EEPROM PATHS
#define MEM_DATE 0                                      //int
#define MEM_TOTALLITRES sizeof(int)                     //float
#define MEM_FLOW MEM_TOTALLITRES + sizeof(float)        //float
#define MEM_MINLEVEL MEM_FLOW + sizeof(float)           //int
#define MEM_MAXLEVEL MEM_MINLEVEL + sizeof(int)         //int
#define MEM_DAILYRUNTIME MEM_MAXLEVEL + sizeof(int)     //int
#define MEM_DAILYCOUNTER MEM_DAILYRUNTIME + sizeof(int) - sizeof(struct day) + sizeof(struct day) * 

//PARAMETERS
#define CONFIGURE_TIMEOUT 20000
#define MIN_DAILYRUNTIME 36000
#define SAVE_LOOP 6000
#define DEBUG_LOOP 500
#define MIN_LEVEL 430
#define MAX_LEVEL 740

struct day{
  int activeSeconds;
  float litres;
};

bool pumpStatus=false, serialStatus=false, switchStatus;
int date, measure, aproxTotalLitres;
int minLevel, maxLevel;
int lastActiveTime, actualActiveTime;
int dailyRuntime, lastRuntime, actualRuntime;
int saveLoopCounter=0, debugLoopCounter=0;
float flow, totalLitres;
struct day today;

void blinky(){
  for(;;){
     if(!Serial){
    measure=analogRead(SENSOR);
  delay(500);
  digitalWrite(RELE, HIGH);
  delay(500);
  digitalWrite(RELE, LOW);
  Serial.println(measure);
  Serial.setTimeout(10);
  }

 else {
  delay(200);
  digitalWrite(RELE, HIGH);
  delay(200);
  digitalWrite(RELE, LOW);
 }
  }
}

void saveData(){
  EEPROM.put(MEM_TOTALLITRES, totalLitres);
  EEPROM.put(MEM_DAILYRUNTIME, dailyRuntime);
  EEPROM.put(MEM_DAILYCOUNTER date, today);
}

// *************************************************** SOLO INICIO ***************************************************************

void loadData(){
  EEPROM.get(MEM_DATE, date);
  EEPROM.get(MEM_TOTALLITRES, totalLitres);
  EEPROM.get(MEM_FLOW, flow);
  EEPROM.get(MEM_MINLEVEL, minLevel);
  EEPROM.get(MEM_MAXLEVEL, maxLevel);
  EEPROM.get(MEM_DAILYRUNTIME, dailyRuntime);
  if (dailyRuntime > MIN_DAILYRUNTIME){
    date++;
    dailyRuntime=0;
    today.activeSeconds=0;
    today.litres=0;
    EEPROM.put(MEM_DATE, date);
    saveData();
  }
  else EEPROM.get (MEM_DAILYCOUNTER date, today);
  lastRuntime=millis();
}

void showData(){
  int i;
  struct day show;
  aproxTotalLitres=(int)totalLitres;
  Serial.print("Total saved days: ");
  Serial.println(date);
  Serial.print("Total consumed water: ");
  Serial.println(aproxTotalLitres);
  Serial.print("Saved average flow: ");
  Serial.println(flow);
  Serial.print("Actual daily runtime: ");
  Serial.println(dailyRuntime);
  Serial.println("\n***************************");
  Serial.println("Daily activity:");
  Serial.println("***************************\n");
  for(i=1; i<=date; i++){
    EEPROM.get(MEM_DAILYCOUNTER date, show);
    Serial.print("Day ");
    Serial.print(date);
    Serial.print(",\t\t Active time: ");
    Serial.print(show.activeSeconds/3600);
    Serial.print("h");
    Serial.print((show.activeSeconds%3600)/60);
    Serial.print("min\t\tWater consumption: ");
    Serial.print(show.litres);
    Serial.println(" L");
  }
  Serial.println("\n***************************\n");
  Serial.print("Counter is running on day ");
  Serial.println(date);
}

void resetCounter(){
  date=1;
  dailyRuntime=0;
  totalLitres=0;
  EEPROM.put(MEM_DATE, date);
  EEPROM.put(MEM_DAILYRUNTIME, dailyRuntime);
  EEPROM.put(MEM_TOTALLITRES, totalLitres);
  Serial.println("Database was reset except flow variable");
}

void updateFlow(){
  flow=Serial.parseFloat();
  EEPROM.put(MEM_FLOW, flow);
  Serial.println("Water flow has been updated");
}

void updateTriggers(){
  minLevel = Serial.parseInt();
  maxLevel = Serial.parseInt();
  EEPROM.put(MEM_MINLEVEL, minLevel);
  EEPROM.put(MEM_MAXLEVEL, maxLevel);
}

void serialUpdate(){
  String command = "";
  showData();
  Serial.println("Available configuration commands:");
  Serial.println("RESET erases all counters, setting day as 1");
  Serial.println("FLOW [L/min, decimals admitted] enables water flow update");
  Serial.println("TRIGGERS [MIN] [MAX] updates ON/OFF triggering limits");
  do{
    Serial.setTimeout(CONFIGURE_TIMEOUT);
    command = Serial.readStringUntil(' ');
  } while (command.equalsIgnoreCase(""));
  if (command.equalsIgnoreCase("RESET")) resetCounter();
  else if (command.equalsIgnoreCase("FLOW")) updateFlow();
  else if (command.equalsIgnoreCase("TRIGGERS")) updateTriggers();
  else Serial.println("Nothing was changed. Counter is initializing...");
}

// *************************************************** SOLO RUNTIME **************************************************************

void serialDebug(){
  if (!(debugLoopCounter%DEBUG_LOOP)){
    if (switchStatus) {
      Serial.print("AUTO");
      Serial.print("\tPump: ");
      if (pumpStatus) Serial.print(" ON");
      else Serial.print("OFF");
    }
    else Serial.print("Pump: ON");
  }
  debugLoopCounter++;
}

void updateData(){
  actualRuntime=actualActiveTime=millis()/1000;
  dailyRuntime+=(lastRuntime-actualRuntime);
  lastRuntime=actualRuntime;
  today.activeSeconds+=(actualActiveTime-lastActiveTime);
  today.litres+=(actualActiveTime-lastActiveTime)*flow/60;
  totalLitres+=(actualActiveTime-lastActiveTime)*flow/60;
  lastActiveTime=actualActiveTime;
  if (serialStatus){
    Serial.print("Usage: ");
    Serial.print(today.activeSeconds/3600);
    Serial.print("h");
    Serial.print((today.activeSeconds%3600)/60);
    Serial.print("min\t\t");
    Serial.print(today.litres);
    Serial.println(" L");
  }
  saveData();
}

void pumpON(){
  digitalWrite(RELE, HIGH);
  pumpStatus=true;
  actualRuntime=lastActiveTime = millis()/1000;
  dailyRuntime+=(lastRuntime-actualRuntime);
  lastRuntime=actualRuntime;
  EEPROM.put(MEM_DAILYRUNTIME, dailyRuntime);
}

void pumpOFF(){
  digitalWrite(RELE, LOW);
  pumpStatus=false;
  updateData();
}

void manual(){
  if(!pumpStatus)pumpON();
  if(!(saveLoopCounter%SAVE_LOOP))updateData();
  saveLoopCounter++;
}

void automatic(){
  measure = analogRead(SENSOR);
  if (measure < minLevel && !pumpStatus) pumpON();
  else if (measure > maxLevel && pumpStatus) pumpOFF();
  else if (pumpStatus) {
    if(!(saveLoopCounter%SAVE_LOOP))updateData();
    saveLoopCounter++;
  }
}

// *************************************************** SETUP *********************************************************************

void setup() {
  pinMode(SENSOR, INPUT);
  pinMode(RELE, OUTPUT);
  pinMode(RELE_5V, OUTPUT);
  pinMode(SWITCH_5V, OUTPUT);
  pinMode(SWITCH, INPUT);

  digitalWrite(RELE_5V, HIGH);
  digitalWrite(RELE, LOW);
  digitalWrite(SWITCH_5V, HIGH);

  Serial.begin(9600);
  Serial.setTimeout(1000);
  blinky();
  loadData();
  if (Serial.available() > 0){
    serialStatus = true;
    serialUpdate();
  }
}

// *************************************************** LOOP **********************************************************************

void loop() {
  switchStatus = digitalRead(SWITCH);
  if (switchStatus) automatic();
  else manual();
  if (serialStatus) serialDebug();
}


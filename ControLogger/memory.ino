
// EEPROM PATHS ***************************************************************************************************************************

#define MEM_FLOW 0                                                  //int
#define MEM_LIMIT_MIN MEM_FLOW + sizeof(int)                        //int
#define MEM_LIMIT_MAX MEM_LIMIT_MIN + sizeof(int)                   //int
#define MEM_CONTROL_MIN MEM_LIMIT_MAX + sizeof(int)                 //byte
#define MEM_CONTROL_MAX MEM_CONTROL_MIN + sizeof(byte)              //byte

#define MEM_DATE MEM_CONTROL_MAX + sizeof(byte)                     //byte
#define MEM_DAILYRUNTIME MEM_DATE + sizeof(byte)                    //unsigned long
#define MEM_TOTALLITRES MEM_DAILYRUNTIME + sizeof(unsigned long)    //int
#define MEM_DAILYCOUNTER MEM_TOTALLITRES + sizeof(int) - sizeof(struct day) + sizeof(struct day) * 

// READ FROM EEPROM ************************************************************************************************************************

void loadParamEEPROM(){
  FCN
  EEPROM.get(MEM_FLOW, flow);
  EEPROM.get(MEM_LIMIT_MIN, limitMin);
  EEPROM.get(MEM_LIMIT_MAX, limitMax);
  EEPROM.get(MEM_CONTROL_MIN, controlMin);
  EEPROM.get(MEM_CONTROL_MAX, controlMax);
  updateMainLog("Param load");
}

void loadDataEEPROM(){
  FCN
  EEPROM.get(MEM_DATE, date);
  EEPROM.get(MEM_TOTALLITRES, totalLitres);
  EEPROM.get(MEM_DAILYRUNTIME, dailyRuntime);
  if (dailyRuntime > MIN_DAILYRUNTIME){
    date++;
    EEPROM.put(MEM_DATE, date);
    dailyRuntime = 0;
    today.activeTime = 0;
    today.litres = 0;
    saveDataEEPROM();
    updateMainLog("NEW DAY");
  }
  else {
    EEPROM.get(MEM_DAILYCOUNTER date, today);
    updateMainLog("PREV DAY");
  }
}

struct day fetchDay(byte date){
  FCN
  struct day fetchingDay;
  return EEPROM.get(MEM_DAILYCOUNTER date, fetchingDay);
}

// WRITE TO EEPROM ***********************************************************************************************************************

void saveDataEEPROM(){
  FCN
  EEPROM.put(MEM_TOTALLITRES, totalLitres);
  EEPROM.put(MEM_DAILYRUNTIME, dailyRuntime);
  EEPROM.put(MEM_DAILYCOUNTER date, today);
  updateMainLog("MEM Updated");
}

void resetCounter(){
  FCN
  date = 1;
  dailyRuntime = 0;
  totalLitres = 0;
  today.activeTime = 0;
  today.litres = 0;
  EEPROM.put(MEM_DATE, date);
  EEPROM.put(MEM_TOTALLITRES, totalLitres);
  EEPROM.put(MEM_DAILYRUNTIME, dailyRuntime);
  EEPROM.put(MEM_DAILYCOUNTER date, today);
  updateMainLog("Memory was reset");
}

// CONFIGURATION SAVER ********************************************************************************************************************

void configurationSaver(){
  FCN
  if (window == configFlow) saveFlow();
  else if (window == configLimitMin) saveLimitMin();
  else if (window == configLimitMax) saveLimitMax();
  else if (window == configControlMin) saveControlMin();
  else if (window == configControlMax) saveControlMax();
  timeLastAction -= SLEEP_TIMEOUT;
}

void saveFlow(){
  FCN
  flow = newFlow;
  EEPROM.put(MEM_FLOW, flow);
  updateMainLog("Flow updated"); 
}

void saveLimitMin(){
  FCN
  limitMin = newLimitMin;
  EEPROM.put(MEM_LIMIT_MIN, limitMin);
  updateMainLog("Limit MIN updated"); 
}

void saveLimitMax(){
  FCN
  limitMax = newLimitMax;
  EEPROM.put(MEM_LIMIT_MAX, limitMax);
  updateMainLog("Limit MAX updated"); 
}

void saveControlMin(){
  FCN
  controlMin = newControlMin;
  EEPROM.put(MEM_CONTROL_MIN, controlMin);
  updateMainLog("Control MIN updated"); 
}

void saveControlMax(){
  FCN
  controlMax = newControlMax;
  EEPROM.put(MEM_CONTROL_MAX, controlMax);
  updateMainLog("Control MAX updated"); 
}


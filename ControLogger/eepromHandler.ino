
// EEPROM PATHS ***************************************************************************************************************************

#define MEM_FLOW 0                                                  //float
#define MEM_LIMIT_MIN MEM_FLOW + sizeof(float)                      //int
#define MEM_LIMIT_MAX MEM_LIMIT_MIN + sizeof(int)                   //int
#define MEM_CONTROL_MIN MEM_LIMIT_MAX + sizeof(int)                 //int
#define MEM_CONTROL_MAX MEM_CONTROL_MIN + sizeof(int)               //int

#define MEM_DATE MEM_CONTROL_MAX + sizeof(int)                      //int
#define MEM_DAILYRUNTIME MEM_DATE + sizeof(int)                     //unsigned long
#define MEM_TOTALLITRES MEM_DAILYRUNTIME + sizeof(unsigned long)    //float
#define MEM_DAILYCOUNTER MEM_TOTALLITRES + sizeof(float) - sizeof(struct day) + sizeof(struct day) * 

// READ FROM EEPROM ************************************************************************************************************************

void loadParamEEPROM(){
  EEPROM.get(MEM_FLOW, flow);
  EEPROM.get(MEM_LIMIT_MIN, limitMin);
  EEPROM.get(MEM_LIMIT_MAX, limitMax);
  EEPROM.get(MEM_CONTROL_MIN, controlMin);
  EEPROM.get(MEM_CONTROL_MAX, controlMax);
  updateMainLog("Param load", "");
}

void loadDataEEPROM(){
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
    updateMainLog("Data load", "NEW DAY");
  }
  else {
    EEPROM.get(MEM_DAILYCOUNTER date, today);
    updateMainLog("Data load", "PREV DAY");
  }
}

// WRITE TO EEPROM ***********************************************************************************************************************

void saveDataEEPROM(){
  EEPROM.put(MEM_TOTALLITRES, totalLitres);
  EEPROM.put(MEM_DAILYRUNTIME, dailyRuntime);
  EEPROM.put(MEM_DAILYCOUNTER date, today);
  updateMainLog("MEM Updated", "");
}

void resetCounter(){
  date = 1;
  dailyRuntime = 0;
  totalLitres = 0;
  today.activeTime = 0;
  today.litres = 0;
  EEPROM.put(MEM_DATE, date);
  EEPROM.put(MEM_TOTALLITRES, totalLitres);
  EEPROM.put(MEM_DAILYRUNTIME, dailyRuntime);
  EEPROM.put(MEM_DAILYCOUNTER date, today);
  updateMainLog("Memory was reset","Starting day 1");
}


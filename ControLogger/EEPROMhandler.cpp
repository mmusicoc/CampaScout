#include "EEPROMhandler.h"            // Incluir HEADER
#include "DISPLAYhandler.h"

EEPROMhandler::EEPROMhandler(DISPLAYhandler* oled, float* flow, int* limitMin, int* limitMax, byte* controlMin, byte* controlMax, byte* date, unsigned long* dailyRuntime, float* totalLitres, day* today){         // Constructor del objeto
  loadParamEEPROM();
  loadDataEEPROM();
  
  // Lo que debe hacer cuando se cree el objeto

}

// READ FROM EEPROM ************************************************************************************************************************

void EEPROMhandler::loadParamEEPROM(){
  EEPROM.get(MEM_FLOW, *_flow);
  EEPROM.get(MEM_LIMIT_MIN, *_limitMin);
  EEPROM.get(MEM_LIMIT_MAX, *_limitMax);
  EEPROM.get(MEM_CONTROL_MIN, *_controlMin);
  EEPROM.get(MEM_CONTROL_MAX, *_controlMax);
  oled->updateMainLog("Param load", "");
}

void EEPROMhandler::loadDataEEPROM(){
  EEPROM.get(MEM_DATE, *_date);
  EEPROM.get(MEM_TOTALLITRES, *_totalLitres);
  EEPROM.get(MEM_DAILYRUNTIME, *_dailyRuntime);
  if (*_dailyRuntime > MIN_DAILYRUNTIME){
    *_date++;
    EEPROM.put(MEM_DATE, *_date);
    *_dailyRuntime = 0;
    _today->activeTime = 0;
    _today->litres = 0;
    EEPROMhandler::saveDataEEPROM();
    oled->updateMainLog("Data load", "NEW DAY");
  }
  else {
    EEPROM.get(MEM_DAILYCOUNTER *_date, *_today);
    oled->updateMainLog("Data load", "PREV DAY");
  }
}

// WRITE TO EEPROM ***********************************************************************************************************************

void EEPROMhandler::saveDataEEPROM(){
  EEPROM.put(MEM_TOTALLITRES, *_totalLitres);
  EEPROM.put(MEM_DAILYRUNTIME, *_dailyRuntime);
  EEPROM.put(MEM_DAILYCOUNTER *_date, *_today);
  oled->updateMainLog("MEM Updated", "");
}

void EEPROMhandler::resetCounter(){
  *_date = 1;
  *_dailyRuntime = 0;
  *_totalLitres = 0;
  _today->activeTime = 0;
  _today->litres = 0;
  EEPROM.put(MEM_DATE, *_date);
  EEPROM.put(MEM_TOTALLITRES, *_totalLitres);
  EEPROM.put(MEM_DAILYRUNTIME, *_dailyRuntime);
  EEPROM.put(MEM_DAILYCOUNTER *_date, *_today);
  oled->updateMainLog("Memory was reset","Starting day 1");
}


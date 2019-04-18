#ifndef eepromH
#define eepromH

#include <EEPROM.h>           // Incluir librerías de las que dependa ésta
#include <Arduino.h>
#include "DISPLAYhandler.h"

// EEPROM PATHS ***************************************************************************************************************************

#define MEM_FLOW 0                                                  //float
#define MEM_LIMIT_MIN MEM_FLOW + sizeof(float)                      //int
#define MEM_LIMIT_MAX MEM_LIMIT_MIN + sizeof(int)                   //int
#define MEM_CONTROL_MIN MEM_LIMIT_MAX + sizeof(int)                 //byte
#define MEM_CONTROL_MAX MEM_CONTROL_MIN + sizeof(byte)              //byte

#define MEM_DATE MEM_CONTROL_MAX + sizeof(byte)                     //byte
#define MEM_DAILYRUNTIME MEM_DATE + sizeof(byte)                    //unsigned long
#define MEM_TOTALLITRES MEM_DAILYRUNTIME + sizeof(unsigned long)    //float
#define MEM_DAILYCOUNTER MEM_TOTALLITRES + sizeof(float) - sizeof(struct day) + sizeof(struct day) * 

// DATA TYPES AND CONSTANTS *************************************************************************************************************

#define MIN_DAILYRUNTIME 36000000

// CLASS DEFINITION *********************************************************************************************************************

class  EEPROMhandler{            //Nombre de la clase
  public:
    // Constructor
    EEPROMhandler(DISPLAYhandler* oled, float* flow, int* limitMin, int* limitMax, byte* controlMin, byte* controlMax, byte* date, unsigned long* dailyRuntime, float* totalLitres, day* today);

    // Public variables
    
    // Public methods
    void saveDataEEPROM();
    void resetCounter();
    
  private:
    // Private variables
    DISPLAYhandler* oled;
    float* _flow;
    int* _limitMin;
    int* _limitMax;
    byte* _controlMin;
    byte* _controlMax;
    byte* _date;
    unsigned long* _dailyRuntime;
    float* _totalLitres;
    day* _today;
    
    // Private methods
    void loadParamEEPROM();
    void loadDataEEPROM();
};

#endif

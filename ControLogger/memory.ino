
// EEPROM PATHS ***************************************************************************************************************************
                                                                    // Tipo de dato:
#define MEM_LIMIT_MIN 0                                             // int                // Direcciones de memoria donde se guardan los parámetros
#define MEM_LIMIT_MAX MEM_LIMIT_MIN + sizeof(int)                   // int                // para que cada vez que se inicie el Arduino se carguen en
#define MEM_CONTROL_MIN MEM_LIMIT_MAX + sizeof(int)                 // byte               // la memoria, pero a la vez sean configurables mediante serial
#define MEM_CONTROL_MAX MEM_CONTROL_MIN + sizeof(byte)              // byte               // sin tener que editar el código in situ.

// READ FROM EEPROM ************************************************************************************************************************

void loadParamEEPROM(){                                           // Función que se ejecuta en el "setup()" que carga en las variables los parámetros almacenados
  FCN                                                             // Sentencia de depuración de la función en la que estamos. Declarada en la pestaña "Debug.h"
  EEPROM.get(MEM_LIMIT_MIN, limitMin);                            // Sentencias de lectura de parámetros de la memoria EEPROM integrada en el Arduino
  EEPROM.get(MEM_LIMIT_MAX, limitMax);
  EEPROM.get(MEM_CONTROL_MIN, controlMin);
  EEPROM.get(MEM_CONTROL_MAX, controlMax);
  if(DEB2) Serial.println("Param load");                          // Mensaje informativo de que se han cargado los parámetros
}

// WRITE TO EEPROM ***********************************************************************************************************************

void saveParamEEPROM(int Lmin, int Lmax, byte Cmin, byte Cmax){
  FCN
  EEPROM.put(MEM_LIMIT_MIN, Lmin);
  EEPROM.put(MEM_LIMIT_MAX, Lmax);
  EEPROM.put(MEM_CONTROL_MIN, Cmin);
  EEPROM.put(MEM_CONTROL_MAX, Cmax);
  if (DEB2) Serial.println("Param saved");
}


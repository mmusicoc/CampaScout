
// EEPROM PATHS ***************************************************************************************************************************
                                                                  // Tipo de dato:
#define MEM_LIMIT_MIN 0                                           // int                // Direcciones de memoria donde se guardan los parámetros
#define MEM_LIMIT_MAX MEM_LIMIT_MIN + sizeof(int)                 // int                // para que cada vez que se inicie el Arduino se carguen en
#define MEM_CONTROL_MIN MEM_LIMIT_MAX + sizeof(int)               // byte               // la memoria, pero a la vez sean configurables mediante serial
#define MEM_CONTROL_MAX MEM_CONTROL_MIN + sizeof(byte)            // byte               // sin tener que editar el código in situ.

// READ FROM EEPROM ************************************************************************************************************************

void loadParamEEPROM(){                                           // Función que se ejecuta en el "setup()" que carga en las variables los parámetros almacenados.
  FCN                                                             // Sentencia de depuración de la función en la que estamos, declarada en la pestaña "Debug.h".
  EEPROM.get(MEM_LIMIT_MIN, limitMin);                            // Sentencias de lectura de parámetros de la memoria EEPROM integrada en el Arduino.
  EEPROM.get(MEM_LIMIT_MAX, limitMax);
  EEPROM.get(MEM_CONTROL_MIN, controlMin);
  EEPROM.get(MEM_CONTROL_MAX, controlMax);
  if(serial) Serial.println("Param load");                        // Mensaje informativo de que se han cargado los parámetros.
}

// WRITE TO EEPROM ***********************************************************************************************************************

void saveLimitMin(){                                              // Función que actualiza en la memoria EEPROM el nuevo valor de "limitMin" enviado por serial.
  FCN
  EEPROM.put(MEM_LIMIT_MIN, limitMin);                            // Sentencia de escritura en la memoria EEPROM.
  if (serial) {                                                   // Si está habilitado el serial, visualizar el nuevo valor guardado.
    Serial.print("New limitMin is: ");
    Serial.println(limitMin);
    Serial.println();
  }
}

void saveLimitMax(){                                              // Lo mismo que "saveLimitMin()", pero para la variable "limitMax".
  FCN
  EEPROM.put(MEM_LIMIT_MAX, limitMax);
  if (serial) {
    Serial.print("New limitMax is: ");
    Serial.println(limitMax);
    Serial.println();
  }
}

void saveControlMin(){                                            // Lo mismo que "saveLimitMin()", pero para la variable "controlMin".
  FCN
  EEPROM.put(MEM_CONTROL_MIN, controlMin);
  if (serial) {
    Serial.print("New controlMin is: ");
    Serial.println(controlMin);
    Serial.println();
  }
}

void saveControlMax(){                                            // Lo mismo que "saveLimitMin()", pero para la variable "controlMax".
  FCN
  EEPROM.put(MEM_CONTROL_MAX, controlMax);
  if (serial) {
    Serial.print("New controlMax is: ");
    Serial.println(controlMax);
    Serial.println();
  }
}

// EEPROM HARD WRITE ***********************************************************************************************************************

void saveParamEEPROM(int Lmin, int Lmax, byte Cmin, byte Cmax){   // Si en algún momento queremos reescribir de golpe unos valores referencia,
  FCN                                                             // escribe todos en la memoria EEPROM.
  EEPROM.put(MEM_LIMIT_MIN, Lmin);
  EEPROM.put(MEM_LIMIT_MAX, Lmax);
  EEPROM.put(MEM_CONTROL_MIN, Cmin);
  EEPROM.put(MEM_CONTROL_MAX, Cmax);
  if (serial) Serial.println("Param saved");
}

void EEPROMresetter(){                                            // Función que guarda los valores de referencia, si queremos usarla hay que activarla en "setup()".
  FCN                        
  controlMin=controlMax=5;                                        // Estos son los valores de referencia.
  limitMin=limitMax=1000;
  saveParamEEPROM(1000,1000,5,5);                                 // Llamada a la función que escribe físicamente los parámetros en la EEPROM.
}


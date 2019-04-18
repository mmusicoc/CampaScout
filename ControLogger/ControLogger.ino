
// MAIN SKETCH **************************************************************************************************************************

#include <EEPROM.h>                       // Incluir las librerías externas necesarias para que funcione
#include "Debug.h"

// ENABLE DEBUG *************************************************************************************************************************

#define DEB1            false             // Para habilitar que se envíe por puerto serial (USB) información de resolución de errores, cambiar a TRUE
#define DEB2            false             // DEB1 muestra las funciones y variables a medida que las ejecuta, DEB2 envía mensajes supletorios

// PIN IDs ******************************************************************************************************************************

#define SENSOR_MIN      A1                // En esta zona se debe configurar el funcionamiento del Arduino:
#define SENSOR_MAX      A3                //    - Pines digitales: el número de pin donde se conecta cada cable
#define SWITCH_MODE     6                 //    - Pines analógicos: el número de pin precedido por "A"
#define SWITCH_PUMP     7                 //    - Parámetros varios, como la velocidad de ejecución de las funciones de lectura (ahorro de energía)
#define RELE            8
#define LED             13
#define CORE_LOOP       30
#define DELAY_LOOP      50

// DATA TYPES AND CONSTANTS *************************************************************************************************************

enum level {underMin = 0, overMax = 1, midLevel = 2};     // Definición de tipo de dato que solo admite esos valores

// GLOBAL VARIABLES DECLARATIONS *******************************************************************************************************

bool switchMode;                          // Modo de funcionamiento: se conmuta con un interruptor: 1 = Auto, 0 = Manual
bool switchPump;                          // Si está en modo Manual, el Arduino comprueba el estado de otro interruptor que activa o desactiva la bomba
bool pumpStatus;                          // Guarda el estado actual de la bomba de llenado
level waterLevel;                         // Variable de tipo leve que guarda el estado actual del nivel de agua en el depósito
byte controlMin, controlMax;              // Parámetros de control del del sensor de agua. Se guardan en EEPROM para que no se pierdan al reiniciar y sean configurables
int limitMin, limitMax;

// SETUP *******************************************************************************************************************************

void setup() {                            // Esta es la rutina estándar que se ejecuta cuando se reinicia el Arduino. ES OBLIGATORIA

  if (DEB1 || DEB2){                      // Si se ha habilitado la depuración de errores, entonces se activa el puerto serial. Si no, se deja apagado para ahorrar
    Serial.begin(38400);                  // Activación del puerto
    Serial.println("Device started");     // Envía por USB un mensaje, y luego salta a una nueva línea
  }
  
  pinMode(SENSOR_MIN, INPUT);             // Activación de los pines I/O, definiendo si son de entrada (sensores) o salida (actuadores)
  pinMode(SENSOR_MAX, INPUT);
  pinMode(RELE, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(SWITCH_MODE, INPUT_PULLUP);     // Para los interruptores, los pines tendrán 2 posibles estados: +5V o flotante
  pinMode(SWITCH_PUMP, INPUT_PULLUP);     // Para evitar problemas, el flotante se fuerza a un estado conocido

  digitalWrite(LED, LOW);                 // Se apaga el LED rojo antes de empezar, para asegurarnos de que conocemos su estado
  
  loadParamEEPROM();                      // Cargar parámetros de la memoria EEPROM en las variables asignadas. Llamada a función de la pestaña "memory"
 // controlMin=controlMax=5;              
 // limitMin=limitMax=1000;
 // saveParamEEPROM(1000,1000,5,5);
}

// LOOP ***********************************************************************************************************************************

void loop() {                             // Una vez terminada la rutina "setup()", se ejecuta "loop()" indefinidamente hasta que se apague el Arduino
  delay(DELAY_LOOP);                      // Una pausa de DELAY_LOOP milisegundos para que no haga tantos bucles y gaste menos energía
  checkSwitchMode();                      // Rutina de control del botón Auto/Manual
  if (switchMode) controlCore(true);      // Dependiendo del estado del botón Auto/Manual, ejecuta la función principal de un modo distinto
  else controlCore(false); 
}


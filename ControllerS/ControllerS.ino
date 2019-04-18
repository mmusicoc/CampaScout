
// PIN IDs ******************************************************************************************************************************

// Pines
#define SENSOR_MIN      A0                // En esta zona se debe configurar el funcionamiento del Arduino:
#define SENSOR_MAX      A2                //    - Pines digitales: el número de pin donde se conecta cada cable.
#define SWITCH_MODE     5                 //    - Pines analógicos: el número de pin precedido por "A".
#define SWITCH_PUMP     7                 //    - Parámetros varios, como la velocidad de ejecución de las funciones de lectura (ahorro de energía).
#define RELE            13
#define LED             13

// Parámetros del programa
#define CORE_LOOP       30
#define DELAY_LOOP      50
#define LIMIT_SENSOR    1020
#define CONTROL_SENSOR  50
#define READ_MARGIN     20

// Modo de uso I/O
#define RELAY_ON        LOW
#define RELAY_OFF       HIGH

// DATA TYPES AND CONSTANTS *************************************************************************************************************

enum level {underMin = 0, overMax = 1, midLevel = 2};     // Definición de tipo de dato que solo admite tres posibilidades de nivel de agua.

// GLOBAL VARIABLES DECLARATIONS *******************************************************************************************************

bool serial = true;                       // Guarda si está disponible y habilitado el puerto serial para transmisión de datos. Enviará mensajes.
bool debug = false;                       // Variable que guarda si la depuración de errores está habilitada,
                                          // enviará las funciones que se ejecutan y otros datos críticos.
bool pumpStatus = false;                  // Guarda el estado actual de la bomba de llenado.
level waterLevel;                         // Variable de tipo leve que guarda el estado actual del nivel de agua en el depósito.

// SETUP *******************************************************************************************************************************

void setup() {                            // Esta es la rutina estándar que se ejecuta cuando se reinicia el Arduino, es OBLIGATORIA. 
  pinMode(SENSOR_MIN, INPUT);             // Activación de los pines I/O, definiendo si son de entrada (sensores) o salida (actuadores).
  pinMode(SENSOR_MAX, INPUT);
  pinMode(RELE, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(SWITCH_MODE, INPUT_PULLUP);     // Para los interruptores, los pines tendrán 2 posibles estados: +5V o flotante,
  pinMode(SWITCH_PUMP, INPUT_PULLUP);     // y para evitar problemas el flotante se fuerza a un estado conocido.

  digitalWrite(LED, LOW);                 // Se apaga el LED rojo antes de empezar, para asegurarnos de que conocemos su estado.
  
  serialStarter();                        // Llama a la función que inicia el puerto serial de transmisión de datos.
  serialHandler();                        // Si está habilitado el puerto, envía el menú de configuración a la consola serial.
}

// LOOP ***********************************************************************************************************************************

void loop() {                             // Una vez terminada la rutina "setup()", se ejecuta "loop()" indefinidamente hasta que se apague el Arduino.
  delay(DELAY_LOOP);                      // Una pausa de DELAY_LOOP milisegundos para que no haga tantos bucles y gaste menos energía.
  controlCore();                          // Dependiendo del estado del botón Auto/Manual, ejecuta la función principal de un modo distinto.
  //Serial.print(digitalRead(SWITCH_MODE));
  //Serial.println(digitalRead(SWITCH_PUMP));
  //Serial.print(analogRead(SENSOR_MIN));
  //Serial.print(" ");
  //Serial.println(analogRead(SENSOR_MAX));
  //Serial.print(digitalGetter(SWITCH_MODE, 30));
  //Serial.println(digitalGetter(SWITCH_PUMP, 30));
  
}


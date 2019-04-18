
// DEFINES ********************************************************************************************************************************

// Pines
#define SENSOR_MIN      A1                // En esta zona se debe configurar el funcionamiento del Arduino:
#define SENSOR_MAX      A3                //    - Pines digitales: el número de pin donde se conecta cada cable.
#define SWITCH_MODE     6                 //    - Pines analógicos: el número de pin precedido por "A".
#define SWITCH_PUMP     7                 //    - Parámetros varios, como la velocidad de ejecución de las funciones de lectura (ahorro de energía).
#define RELE            13
#define LED             13
#define FLOWMETER       2

// Parámetros del programa
#define CORE_LOOP       30
#define DELAY_LOOP      100
#define LIMIT_SENSOR    1000
#define CONTROL_SENSOR  6
#define FLOWMETER_K     3000    // counts/litre

// Modo de uso I/O
#define RELAY_ON        LOW
#define RELAY_OFF       HIGH
#define SENSOR_HIGH     >=

// DATA TYPES AND CONSTANTS *************************************************************************************************************

enum level {underMin = 0, overMax = 1, midLevel = 2};     // Definición de tipo de dato que solo admite tres posibilidades de nivel de agua.

// GLOBAL VARIABLES DECLARATIONS *******************************************************************************************************

bool serial = true;                       // Guarda si está disponible y habilitado el puerto serial para transmisión de datos. Enviará mensajes.
bool debug = false;                       // Variable que guarda si la depuración de errores está habilitada,
                                          // enviará las funciones que se ejecutan y otros datos críticos.
bool pumpStatus = false;                  // Guarda el estado actual de la bomba de llenado.
level waterLevel;                         // Variable de tipo level que guarda el estado actual del nivel de agua en el depósito.
int flowmeterCounts = 0;                  // Aumentará cada vez que el caudalímetro manda una señal, cada cierto tiempo se guardará en la SD.

// SETUP *******************************************************************************************************************************

void setup() {                            // Esta es la rutina estándar que se ejecuta cuando se reinicia el Arduino, es OBLIGATORIA. 
  pinMode(SENSOR_MIN, INPUT);             // Activación de los pines I/O, definiendo si son de entrada (sensores) o salida (actuadores).
  pinMode(SENSOR_MAX, INPUT);
  pinMode(RELE, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(SWITCH_MODE, INPUT_PULLUP);     // Para los interruptores, los pines tendrán 2 posibles estados: +5V o flotante,
  pinMode(SWITCH_PUMP, INPUT_PULLUP);     // y para evitar problemas el flotante se fuerza a un estado conocido.
  pinMode(FLOWMETER, INPUT);

  attachInterrupt(digitalPinToInterrupt(FLOWMETER), flowMeter, RISING); // Ejecuta la función "flowMeter()" cada vez que recibe señal del caudalímetro.

  digitalWrite(LED, LOW);                 // Se apaga el LED rojo antes de empezar, para asegurarnos de que conocemos su estado.
  
  serialStarter();                        // Llama a la función que inicia el puerto serial de transmisión de datos.
  serialHandler();                        // Si está habilitado el puerto, envía el menú de configuración a la consola serial.
}

// LOOP ***********************************************************************************************************************************

void loop() {                             // Una vez terminada la rutina "setup()", se ejecuta "loop()" indefinidamente hasta que se apague el Arduino.
  delay(DELAY_LOOP);                      // Una pausa de DELAY_LOOP milisegundos para que no haga tantos bucles y gaste menos energía.
  controlCore();                          // Dependiendo del estado del botón Auto/Manual, ejecuta la función principal de un modo distinto.
}


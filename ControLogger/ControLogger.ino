
// MAIN SKETCH **************************************************************************************************************************

#include <SSD1306Ascii.h>
#include <SSD1306AsciiAvrI2c.h>
#include <EEPROM.h>
#include "Debug.h"

// PIN IDs ******************************************************************************************************************************

#define I2C_ADDRESS     0x3C
#define SENSOR_MIN      A0
#define SENSOR_MAX      A3
#define ENCODER_CLK     2
#define ENCODER_A       3
#define ENCODER_B       4
#define OLED_ENABLE     5
#define SWITCH_MODE     6
#define SWITCH_PUMP     7
#define SDA             A4
#define SCL             A5
#define RELE            8
#define OLED_RESET      9

// PARAMETERS 36000000 **************************************** **************************************************************************

#define MIN_DAILYRUNTIME    36000000
#define CORE_LOOP           100
#define SAVE_LOOP           1000
#define CHAR_A              System5x7
#define CHAR_B              Callibri10
#define CHAR_C              Stang5x7
#define CHAR_D              lcd5x7
#define CHAR_E              lain5x7
#define CHAR_WIDTH          6
#define SET_VALUE_POS       32
#define SLEEP_TIMEOUT       15000

// DATA TYPES AND CONSTANTS *************************************************************************************************************

struct day{
  unsigned long activeTime;
  float litres;
};
enum page {mainM = 0, configM = 1, resetM = 2,
           off = 3, mainW = 4, viewD = 5,
           configFlow = 6,
           configLimitMin = 7,
           configLimitMax = 8,
           configControlMin = 9,
           configControlMax = 10};
enum level {underMin, overMax, midLevel};

const byte itemsPerMenu [] = {4, 6, 2};    // Número de elementos por página
const byte lineWindow[] = {0, 16, 32, 48, 64};
const byte lineMenu [] = {0, 8, 11, 20, 29, 38, 47, 56};

// GLOBAL VARIABLES DECLARATIONS *******************************************************************************************************

SSD1306AsciiAvrI2c oled;           // Incializar el objeto que controla la pantalla

page window, prevWindow;
byte menuItem, prevMenuItem;
volatile bool buttonWasPressed;
volatile char rotationEncoder;

bool switchMode, switchPump, pumpStatus;                // Switch Mode 1 = Auto; 0 = Manual
level waterLevel;
byte date, controlMin, controlMax, newControlMin, newControlMax;
int limitMin, limitMax, newLimitMin, newLimitMax;
unsigned long dailyRuntime;
unsigned long timeLastAction;
int flow, newFlow, totalLitres;                                  // Flow is in mL/min
struct day today;

// SETUP *******************************************************************************************************************************

void setup() {

  Serial.begin(38400);
  Serial.println("Device started");
  
  pinMode(SENSOR_MIN, INPUT);
  pinMode(SENSOR_MAX, INPUT);
  pinMode(RELE, OUTPUT);
  
  pinMode(ENCODER_CLK, INPUT_PULLUP);
  pinMode(ENCODER_A, INPUT);
  pinMode(ENCODER_A, INPUT);
  
  attachInterrupt(digitalPinToInterrupt(ENCODER_CLK), pushEncoder, FALLING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_A), rotateEncoder, FALLING);

  pinMode(SWITCH_MODE, INPUT_PULLUP);
  pinMode(SWITCH_PUMP, INPUT_PULLUP);

  // Poner a punto la pantalla
  
  pinMode(OLED_ENABLE, OUTPUT);
  digitalWrite(OLED_ENABLE, HIGH);
  delay(1000);
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
  delay(1000);

  // Inicializar las variables
  
  buttonWasPressed = false;
  window = mainW;
  prevWindow = off;
  menuItem = 1;
  prevMenuItem = 0;

  // Cargar datos y parámetros de la memoria
  
  loadParamEEPROM();
  loadDataEEPROM();
  timeLastAction = dailyRuntime;
}

// LOOP ***********************************************************************************************************************************

void loop() {
  delay(5000);
  checkInteractionGUI();
  checkSwitchMode();
  if (switchMode) controlCore(true);
  else controlCore(false);
  countDownSleep();  
}


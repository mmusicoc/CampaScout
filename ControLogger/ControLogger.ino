#include "oledHandler.h"
#include <EEPROM.h>

// PIN IDs ******************************************************************************************************************************

#define SENSOR_MIN      A0
#define SENSOR_MAX      A3
#define ENCODER_CLK     2
#define ENCODER_A       3
#define ENCODER_B       4
#define SWITCH_MODE     5
#define SWITCH_PUMP     6
#define SDA             A4
#define SCL             A5
#define OLED_ENABLE     7
#define RELE            8
#define OLED_RESET      9

// PARAMETERS 36000000 ******************************************************************************************************************

#define MENU_TIMEOUT 8000
#define MIN_DAILYRUNTIME 36000000
#define CORE_LOOP 100
#define SAVE_LOOP 1000
#define CHAR_WIDTH 5
#define SLEEP_TIMEOUT 15000

// DATA TYPES AND CONSTANTS *************************************************************************************************************

struct day{
  unsigned long activeTime;
  float litres;
};
enum orientation {center, down, up, right, left};
enum page {off = 0, mainW = 1, mainM = 2, viewD = 3, configM = 4,  configFlow = 5, configCond = 6, configComp = 7, resetM = 8};
enum level {underMin, overMax, midLevel};

const byte itemsPerPage [] = {0, 0, 4, 0, 4, 1, 2, 1, 2};    // Número de elementos por página
const byte line[] = {0, 15, 30, 45, 60};
const byte lineMenu [] = {0, 10, 16, 32, 48, 64};

// GLOBAL VARIABLES DECLARATIONS *******************************************************************************************************

OledHandler oled();

page window, prevWindow;
byte menuItem, prevMenuItem;
volatile bool buttonWasPressed;
volatile char rotationEncoder;

bool switchMode, switchPump, pumpStatus;                // Switch Mode 1 = Auto; 0 = Manual
level waterLevel;
byte date, limitMin, limitMax, controlMin, controlMax;
unsigned long dailyRuntime;
unsigned long timeLastAction;
float flow, totalLitres;                                // Flow is in L/min
struct day today;

// SETUP *******************************************************************************************************************************

void setup() {
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

  pinMode(OLED_ENABLE, OUTPUT);
  digitalWrite(OLED_ENABLE, HIGH);

  loadParamEEPROM();
  loadDataEEPROM();
  
  buttonWasPressed = false;
  timeLastAction = dailyRuntime;
  window = mainW;
  prevWindow = off;
  menuItem = 1;
  prevMenuItem = 0;

  oled.mainWindow();
}

// LOOP ***********************************************************************************************************************************

void loop() {
  checkInteractionGUI();
  checkSwitchMode();
  if (switchMode) controlCore(true);
  else controlCore(false);
  countDownSleep();
}


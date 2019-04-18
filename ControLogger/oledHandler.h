#ifndef oh
#define oh

#include <Adafruit_SSD1306.h>

class OledHandler {
  public:
    //Constructor
    OledHandler(bool msg = true);

    //Methods
    void updateMainLog(String message1, String message2);
    void countDownSleep();
    void mainWindow();
    void mainMenu();
    void visualizeData();
    void updateParamsMenu();
    void resetDataPage();

  private:
    enum page {off = 0, mainW = 1, mainM = 2, viewD = 3, configM = 4,  configFlow = 5, configCond = 6, configComp = 7, resetM = 8};

    
    void prepareDisplay();
    void drawMenuTitle(String message);
    void drawMenuItem(page windowItem, byte numItem, String nameItem);
    void oledOFF();
};

#endif

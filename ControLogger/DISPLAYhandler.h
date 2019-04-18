#ifndef displayH
#define displayH

#include <Adafruit_SSD1306.h>           // Incluir librerías de las que dependa ésta

// DATA TYPES AND CONSTANTS *************************************************************************************************************

#define OLED_RESET 9

struct day{
  unsigned long activeTime;
  float litres;
};

// CLASS DEFINITION *********************************************************************************************************************

class  DISPLAYhandler{            //Nombre de la clase
  public:
    // Constructor
    DISPLAYhandler();                         // Nombre del objeto


    // Public variables
    String message1, message2;
    enum orientation {center, down, up, right, left};
    enum page {off = 0, mainW = 1, mainM = 2, viewD = 3, configM = 4,  configFlow = 5, configCond = 6, configComp = 7, resetM = 8};

    
    
    // Public methods
    void updateMainLog(String message1, String message2);

  private:

    // Private variables
    Adafruit_SSD1306 Display;

    int itemsPerPage[9] = {0, 0, 4, 0, 4, 1, 2, 1, 2};    // Número de elementos por página
    int line[5] = {0, 15, 30, 45, 60};
    int lineMenu[6] = {0, 10, 16, 32, 48, 64};

    page window, prevWindow;
    byte menuItem, prevMenuItem;

    // Private methods
    
};

#endif

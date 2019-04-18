#include "DISPLAYhandler.h"            // Incluir HEADER

DISPLAYhandler::DISPLAYhandler(){         // Constructor del objeto
  // Lo que debe hacer cuando se cree el objeto
  
  Adafruit_SSD1306 Display(OLED_RESET);
  Display.begin(SSD1306_SWITCHCAPVCC, 0x3D);
  Display.clearDisplay();
  Display.display();
  delay(1000);

  // Número de elementos por página
  


}

  

// METHODS ******************************************************************************************************************************

  // Funciones de la clase

void DISPLAYhandler::updateMainLog(String message1, String message2){
//  mainWindow();
  Display.setCursor(0, line[3]);
  Display.print(message1);
  Display.setCursor(0, line[4]);
  Display.print(message2);
  Display.display();
  delay(5000);
}

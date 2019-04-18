#include "oledHandler.h"

OledHandler::OledHandler(){
  // Creates the object

  Adafruit_SSD1306 Display(OLED_RESET);
  Display.begin(SSD1306_SWITCHCAPVCC, 0x3D);
  Display.clearDisplay();
  Display.display();
  delay(1000);
  
}


// OLED DISPLAY ******************************************************************************************************************************

void OledHandler::updateMainLog(String message1, String message2){
  mainWindow();
  Display.setCursor(0, line[3]);
  Display.print(message1);
  Display.setCursor(0, line[4]);
  Display.print(message2);
  Display.display();
  delay(5000);
}

void OledHandler::prepareDisplay(){
  Display.clearDisplay();
  Display.setTextSize(1);
  Display.setTextColor(BLACK, WHITE);
}

void OledHandler::drawMenuTitle(String message){
  Display.setCursor((64 - message.length() * CHAR_WIDTH) / 2, lineMenu[0]);  // Ajustar el ancho de cada caracter para que el título quede centrado
  Display.print(message);
  Display.drawFastHLine(0, lineMenu[1], 83, BLACK);
}

void OledHandler::drawMenuItem(page windowItem, byte numItem, String nameItem){
  if (window == windowItem && menuItem == numItem){
    Display.setTextColor(WHITE, BLACK);}
  else Display.setTextColor(BLACK, WHITE);
  Display.print("> ");
  Display.print(nameItem);
}

void OledHandler::countDownSleep(){
  if (dailyRuntime - timeLastAction > SLEEP_TIMEOUT) {
    if (window == mainW) oledOFF();
    else {
      mainWindow();
      timeLastAction = millis();
    }
  }
}

// MAIN WINDOW ******************************************************************************************************************************

void OledHandler::oledOFF(){
  Display.clearDisplay();
  window = off;
  menuItem = 1;
  digitalWrite(OLED_ENABLE, LOW);
}

void OledHandler::mainWindow(){
  int hour = today.activeTime / 3600000;
  int mins = (today.activeTime % 3600000) / 60000;
  int aproxTodayLitres = (int)today.litres;
  prepareDisplay();

  // Visualizar estado de la bomba
  
  Display.setCursor(0, line[0]); 
  Display.print("PUMP: ");
  if (pumpStatus == true) Display.print("ON");
  else Display.print("OFF");

  // Visualizar estado del depósito
  
  Display.setCursor(60, line[0]); 
  if (waterLevel == underMin) Display.print("LOW");
  else if (waterLevel == midLevel) Display.print("MID");
  else Display.print("MAX");

  // Visualizar fecha y hora
  Display.setCursor(0, line[1]);
  Display.print(date);
  Display.print(" - ");
  Display.print(hour);
  Display.print(":");
  Display.print(mins);

  // Visualizar consumo diario

  Display.setCursor(60, line[1]);
  Display.print(aproxTodayLitres);
  Display.print(" L");

  //Visualizar consumo total

  Display.setCursor(0, line[2]);
  Display.print(totalLitres);
  Display.print(" L");

  Display.display();
}

// MAIN MENU ********************************************************************************************************************************

void OledHandler::mainMenu(){
  prepareDisplay();
  drawMenuTitle("MAIN MENU");

  Display.setCursor(0, lineMenu[2]);
  drawMenuItem(mainM, 1, "View data");
  Display.setCursor(0, lineMenu[3]);
  drawMenuItem(mainM, 2, "Update params");
  Display.setCursor(0, lineMenu[4]);
  drawMenuItem(mainM, 3, "Reset mem");
  Display.setCursor(0, lineMenu[5]);
  drawMenuItem(mainM, 4, "Back");

  Display.display();
}

// VISUALIZATION OF SAVED DATA ***************************************************************************************************************

void OledHandler::visualizeData(){

}

// UPDATE PARAMETERS MENU *******************************************************************************************************************

void OledHandler::updateParamsMenu(){
  prepareDisplay();
  drawMenuTitle("UPDATE PARAMS");
 
  Display.setCursor(0, lineMenu[2]);
  drawMenuItem(configM, 1, "Flow");
  Display.setCursor(0, lineMenu[3]);
  drawMenuItem(configM, 2, "Conductivity");
  Display.setCursor(0, lineMenu[4]);
  drawMenuItem(configM, 3, "Comprobations");
  Display.setCursor(0, lineMenu[5]);
  drawMenuItem(configM, 4, "Back");

  Display.display();
}

// RESET DATA CONFIMATION PAGE *****************************************************************************************************************

void OledHandler::resetDataPage(){
  prepareDisplay();
  drawMenuTitle("RESET CONFIRM");
  
  Display.setCursor(0, lineMenu[2]);
  drawMenuItem(resetM, 1, "Back - not reset");
  Display.setCursor(0, lineMenu[3]);
  drawMenuItem(resetM, 2, "Reset mem to 0");

  Display.display();
}

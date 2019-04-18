
// OLED DISPLAY ******************************************************************************************************************************

void updateMainLog(String message1){
  FCN
  mainWindow();
  oled.println(message1);
  delay(5000);
}

void prepareDisplay(const uint8_t* sizeFont){
  FCN
  oled.clear();
  oled.setFont(sizeFont);
}

void drawMenuTitle(String message){
  FCN
  oled.setFont(CHAR_A);
  oled.print("    ");
  oled.println(message);
}

void drawMenuItem(page windowItem, byte numItem, String nameItem){
  FCN
  if (window == windowItem && menuItem == numItem) oled.print("> ");
  else oled.print("  ");
  oled.println(nameItem);
}

// MAIN WINDOW ******************************************************************************************************************************

void oledOFF(){
  FCN
  oled.clear();
  window = off;
  menuItem = 1;
  digitalWrite(OLED_ENABLE, LOW);
}

void mainWindow(){
  FCN
  int hour = today.activeTime / 3600000;
  int mins = (today.activeTime % 3600000) / 60000;
  int aproxTodayLitres = (int)today.litres;
  prepareDisplay(Verdana12);

  oled.print("PUMP: ");                                   // Visualizar estado de la bomba
  if (pumpStatus == true) oled.print("ON");
  else oled.print("OFF");
  oled.print("            ");                                   // Visualizar estado del depósito
  if (waterLevel == underMin) oled.println("LOW");
  else if (waterLevel == midLevel) oled.println("MID");
  else oled.println("MAX");

  oled.print(date);                                       // Visualizar fecha y hora
  oled.print(" - ");
  oled.print(hour);
  oled.print(":");
  oled.print(mins);
  oled.print("          ");                                       // Visualizar consumo diario
  oled.print(aproxTodayLitres);
  oled.println(" mL");

  oled.print(totalLitres);                                    //Visualizar consumo total
  oled.println(" mL");
}

// MAIN MENU ********************************************************************************************************************************

void mainMenu(){
  FCN
  String labels[] = {"MAIN MENU", "View data", "Update params", "Reset mem", "Back"};
  prepareDisplay(CHAR_A);
  drawMenuTitle(labels[0]);
  for(int i = 1; i <= 5; i++){
    oled.println();
    drawMenuItem(mainM, i, labels[i]);
  }
}

// UPDATE PARAMETERS MENU *******************************************************************************************************************

void updateParamsMenu(){
  FCN
  String labels[] = {"UPDATE PARAMS", "Flow", "Limit MIN", "Limit MAX", "Comprobations MIN", "Comprobations MAX", "Back"};
  prepareDisplay(CHAR_A);
  drawMenuTitle(labels[0]);
  for(int i = 1; i <= 6; i++){
    oled.println();
    drawMenuItem(configM, i, labels[i]);
  }
}

// RESET DATA CONFIMATION PAGE *****************************************************************************************************************

void resetDataMenu(){
  FCN
  String labels[] = {"RESET CONFIRM", "Back - not reset", "Reset mem to 0"};
  prepareDisplay(CHAR_A);
  drawMenuTitle(labels[0]);
  for(int i = 1; i <= 2; i++){
    oled.println();
    drawMenuItem(configM, i, labels[i]);
  }
}

// VISUALIZATION OF SAVED DATA ***************************************************************************************************************

void visualizeData(){
  FCN
  prepareDisplay(CHAR_A);
  for(int i = menuItem; i <= date; i++) {
    visualizeDay(i);
  }
  for(int j = menuItem; j > 1; j--){
    for(int k = 1; k <= 25; k++) oled.print(" ");
    oled.println();
  }
}

void visualizeDay(byte date){
  FCN
  struct day fetchedDay = fetchDay(date);
  oled.setCursor(0, lineWindow[date - 1]);
  oled.print("Day ");
  oled.print(date);
  oled.print(":");
  oled.print(fetchedDay.litres);
  oled.println(" mL/dia");
}


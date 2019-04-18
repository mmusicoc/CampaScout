
// UPDATE CONFIG *****************************************************************************************************************************

void updaterPage(int previous, String pageTitle, String label){
  FCN
  prepareDisplay(CHAR_B);
  drawMenuTitle(pageTitle);
  oled.setCursor(0, lineMenu[1]);
  oled.print("Prev: ");
  oled.print(previous);
  oled.print(label);
  oled.setCursor(0, lineMenu[2]);
  oled.print("Set: ");
  for(;!countDownSleep();){
  }
}

void refreshFlow(){
  FCN
  newFlow = flow + rotationEncoder;
  oled.setCursor(SET_VALUE_POS, lineMenu[2]);
  oled.print(newFlow);
  oled.print(" mL/min");
}

void refreshLimitMin(){
  FCN
  newLimitMin = limitMin + rotationEncoder;
  oled.setCursor(SET_VALUE_POS, lineMenu[2]);
  oled.print(newLimitMin);
  oled.print(" / 1024");
}

void refreshLimitMax(){
  FCN
  newLimitMax = limitMax + rotationEncoder;
  oled.setCursor(SET_VALUE_POS, lineMenu[2]);
  oled.print(newLimitMax);
  oled.print(" / 1024");
}

void refreshControlMin(){
  FCN
  newControlMin = controlMin + rotationEncoder;
  oled.setCursor(SET_VALUE_POS, lineMenu[2]);
  oled.print(newControlMin);
  oled.print(" cycles");
}

void refreshControlMax(){
  FCN
  newControlMax = controlMax + rotationEncoder;
  oled.setCursor(SET_VALUE_POS, lineMenu[2]);
  oled.print(newControlMax);
  oled.print(" cycles");
}


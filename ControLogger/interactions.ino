
// SWITCHES HANDLER ****************************************************************************************************************************

void checkSwitchMode(){
  FCN
  static int coreLoop;
  if (coreLoop == CORE_LOOP) {
    int valido = 0;
    coreLoop = 0;
    for (int i = 0; i < 4; i++) {
      if (digitalRead(SWITCH_MODE) == HIGH) valido++;
      else valido--;
      delayMicroseconds(20);
    }
    if (valido == 4) switchMode = true;
    else if (valido == -4) switchMode = false;
  }
}

void checkSwitchPump(){
  FCN
  int valido = 0;
  for (int i = 0; i < 4; i++) {
    if (digitalRead(SWITCH_MODE) == HIGH) valido++;
    else valido--;
    delayMicroseconds(20);
  }
  if (valido == 4) switchPump = true;
  else if (valido == -4) switchPump = false;
}

// ENCODER HANDLER ****************************************************************************************************************************

void pushEncoder(){
  FCN
  buttonWasPressed = true;
  delayMicroseconds(50);
}

void rotateEncoder(){
  FCN
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();
  if (interruptTime - lastInterruptTime > 2) {
    if (digitalRead(ENCODER_B) == LOW) rotationEncoder--;
    else rotationEncoder++;
    rotationEncoder = constrain(rotationEncoder, -1, +1);
    lastInterruptTime = interruptTime;
    checkInteractionGUI();
  }
}

void checkInteractionGUI(){
  FCN
  if(buttonWasPressed == true){
    timeLastAction = millis();
    actionPress();
    buttonWasPressed = false;
  }
  if (rotationEncoder != 0){
    timeLastAction = millis();
    actionRotation();
    rotationEncoder = 0;
  }
  delay(50);
}

bool countDownSleep(){
  FCN
  DEBUG(timeLastAction);
  if (dailyRuntime - timeLastAction > SLEEP_TIMEOUT) {
    DEBUG(window);
    if (window == mainW) {}//oledOFF()
    else {
      mainWindow();
      timeLastAction = millis();
    }
    return 1;
  }
  return 0;
}


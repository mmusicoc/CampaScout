
// SWITCHES HANDLER ****************************************************************************************************************************

void checkSwitchMode(){
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
  buttonWasPressed = true;
  delayMicroseconds(50);
}

void rotateEncoder(){
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();
  if (interruptTime - lastInterruptTime > 5) {
    if (digitalRead(ENCODER_B) == LOW) rotationEncoder--;
    else rotationEncoder++;
    rotationEncoder = constrain(rotationEncoder, -5, +5);
    lastInterruptTime = interruptTime;
  }
}

void checkInteractionGUI(){
  if(buttonWasPressed == true){
    timeLastAction = millis();
    actionPress();
    buttonWasPressed = false;
  }
  if (rotationEncoder != 0){
    timeLastAction = millis();
    if (window == mainM || window == configM || window == resetM) navigateMenu();
    else if (window == viewD) scrollData();
    else if (window == configFlow) updateFlow();
    else if (window == configCond) updateConductivity();
    else if (window == configComp) updateComprobations();
  }
  delay(50);
}


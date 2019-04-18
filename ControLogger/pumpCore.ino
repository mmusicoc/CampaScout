
// PUMP CONTROLLER CORE *******************************************************************************************************************

void controlCore(bool mode){                          // Switch Mode 1 = Auto; 0 = Manual
  static int coreLoop, saveLoop;

  // Control de la bomba
  if (coreLoop == CORE_LOOP) {
    coreLoop = 0;
    if (mode){
      getSensors();
      if (waterLevel == underMin && !pumpStatus) pumpON();
      else if (waterLevel == overMax && pumpStatus) pumpOFF();
    }
    else {
      checkSwitchPump();
      if (switchPump && !pumpStatus) pumpON();
      else if (!switchPump && pumpStatus) pumpOFF();
    }
  }
  else coreLoop++;

  delay(50);
}

void pumpON(){
  FCN
  digitalWrite(RELE, LOW);
  pumpStatus = true;
  if(DEB2) Serial.println("LOW -> Pump ON");
  digitalWrite(LED, HIGH);
}

void pumpOFF(){
  FCN
  digitalWrite(RELE, HIGH);
  pumpStatus = false;
  if(DEB2) Serial.println("HIGH -> Pump OFF");
  digitalWrite(LED, LOW);
}


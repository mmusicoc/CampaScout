
// PUMP CONTROLLER CORE *******************************************************************************************************************

void controlCore(bool mode){                          // Switch Mode 1 = Auto; 0 = Manual
  static int coreLoop, saveLoop;

  // Control de la bomba
  FCN
  if (coreLoop == CORE_LOOP) {
    coreLoop = 0;
    if (mode){
      getSensors();
      if (waterLevel == underMin && !pumpStatus) pumpON();
      else if (waterLevel == overMax && pumpStatus) pumpOFF();
      else updateCore();
    }
    else {
      checkSwitchPump();
      if (switchPump && !pumpStatus) pumpON();
      else if (!switchPump && pumpStatus) pumpOFF();
      else updateCore();
    }
  }
  else coreLoop++;

  // Actualizar datos en memoria
  
  if (saveLoop == SAVE_LOOP){
    saveLoop = 0;
    saveDataEEPROM();
  }
  else saveLoop++;

  delay(50);
}

void updateCore(){
  FCN
  static unsigned long actualRuntime, lastRuntime = millis(); // Si este valor se asigna en cada llamada, hacer variable global e inicializar en setup()
  float timeIncrease;
  actualRuntime = millis();
  timeIncrease = (actualRuntime - lastRuntime);
  lastRuntime = actualRuntime;
  dailyRuntime += timeIncrease;
  if (pumpStatus){
    today.activeTime += timeIncrease;
    today.litres += timeIncrease / 60 * flow;
    totalLitres += timeIncrease / 60 * flow;
  }
}

void pumpON(){
  FCN
  digitalWrite(RELE, LOW);
  updateCore();
  saveDataEEPROM;
  pumpStatus = true;
  updateMainLog("LOW -> Pump ON");
}

void pumpOFF(){
  FCN
  digitalWrite(RELE, HIGH);
  updateCore();
  saveDataEEPROM();
  pumpStatus = false;
  updateMainLog("HIGH -> Pump OFF");
}

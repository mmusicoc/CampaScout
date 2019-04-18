
// WATER LEVEL SENSOR ****************************************************************************************************************************

bool getSensorMin(){
  int i;
  int valido = 0;
  int measure;
  for (i = 0; i < controlMin; i++){
    measure = analogRead(SENSOR_MIN);
    if (measure >= limitMin) valido++;
    delayMicroseconds(100);
  }
  if (valido == controlMin) return 1;
  else return 0;
}

bool getSensorMax(){
  int i;
  int valido = 0;
  int measure;
  for (i=0; i < controlMax; i++){
    measure = analogRead(SENSOR_MAX);
    //Serial.println(measure);
    if (measure >= limitMax) valido++;
    delayMicroseconds(100);
  }
  if (valido == controlMax) return 1;
  else return 0;
}

void getSensors(){
  FCN
  if (getSensorMax()) {
    waterLevel = overMax;
    if (DEB2) Serial.println("OVER MAX");
  }
  else if(getSensorMin()) {
    waterLevel = midLevel;
    if(DEB2) Serial.println("MIDDLE LEVEL");
  }
  else {
    waterLevel = underMin;
    if(DEB2) Serial.println("UNDER MIN");
  }
}


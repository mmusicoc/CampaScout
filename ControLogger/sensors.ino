
// WATER LEVEL SENSOR ****************************************************************************************************************************

bool getSensorMin(){
  FCN
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
  FCN
  int i;
  int valido = 0;
  int measure;
  for (i=0; i < controlMax; i++){
    measure = analogRead(SENSOR_MAX);
    if (measure >= limitMax) valido++;
    delayMicroseconds(100);
  }
  if (valido == controlMax) return 1;
  else return 0;
}

void getSensors(){
  FCN
  bool a = getSensorMin();
  bool b = getSensorMax();
  if (!a) waterLevel = underMin;
  else if(b) waterLevel = overMax;
  else waterLevel = midLevel;
}


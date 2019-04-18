
// PRESS BUTTON ACTION *******************************************************************************************************************

void actionPress(){
  FCN
  if (window == off) {window = mainW; mainWindow();}                    // Pantalla desactivada -> Main Window
  else if (window == mainW) {window = mainM; menuItem = 1; mainMenu();}  // Main Window -> Main Menu
  else if (window == mainM) {       // Main Menu -> 
    switch(menuItem) {
      case 1: {window = viewD;   menuItem = 1;  visualizeData();    break;}
      case 2: {window = configM; menuItem = 1;  updateParamsMenu(); break;}
      case 3: {window = resetM;  menuItem = 1;  resetDataMenu();    break;}
      case 4: {window = mainW;   menuItem = 1;  mainWindow();       break;}
    }
  }
  else if (window == viewD) {       // Visualize Data -> no action
  }
  else if (window == configM) {     // Update Params Menu ->
   switch(menuItem) {
      case 1: {window = configFlow;       menuItem = 1;   updaterPage(flow, "FLOW", " mL/min");                           break;}
      case 2: {window = configLimitMin;   menuItem = 1;   updaterPage(limitMin, "LIMIT MIN", " / 1024");                  break;}
      case 3: {window = configLimitMax;   menuItem = 1;   updaterPage(limitMax, "LIMIT MAX", " / 1024");                  break;}
      case 4: {window = configControlMin; menuItem = 1;   updaterPage((int)controlMin, "COMPROBATIONS MIN", " cycles");   break;}
      case 5: {window = configControlMax; menuItem = 1;   updaterPage((int)controlMax, "COMPROBATIONS MAX", " cycles");   break;}
      case 6: {window = mainM;            menuItem = 2;   mainMenu();                                                     break;}
    }
  }
  else if (window == resetM) {    // Reset Menu ->
    switch(menuItem) {
      case 1: {window = mainM;  menuItem = 3;                   break;}
      case 2: {window = mainW;  menuItem = 1;  resetCounter();  break;}
    }
  }
  else configurationSaver();
}

// ROTATE ACTION IN MENU ******************************************************************************************************************

void actionRotation(){
  FCN
  if (window == off) mainWindow();
  else if (window == mainM || window == configM || window == resetM) navigateMenu();
  else if (window == viewD) scrollData();
  else if (window == configFlow) refreshFlow();
  else if (window == configLimitMin) refreshLimitMin();
  else if (window == configLimitMax) refreshLimitMax();
  else if (window == configControlMin) refreshControlMin();
  else if (window == configControlMax) refreshControlMax();
}

void navigateMenu(){
  FCN
  if (rotationEncoder == -1) menuUP();
  else menuDOWN();
  rotationEncoder = 0;
}

void menuUP(){
  FCN
  if (menuItem == 1) menuItem = itemsPerMenu[window];
  else menuItem--;
}

void menuDOWN(){
  FCN
  if (menuItem == itemsPerMenu[window]) menuItem = 1;
  else menuItem++;
}

// ROTATE ACTION IN DATA PAGE *******************************************************************************************************************

void scrollData(){
  FCN
  if (rotationEncoder == -1) menuUP();
  else menuDOWN();
  rotationEncoder = 0;
}

void dataUP(){
  FCN
  if (menuItem != 1) menuItem--;
  else menuItem = 1;
}

void dataDOWN(){
  FCN
  if (menuItem != date - 8) menuItem++;
  else menuItem = date - 8;
}



// PRESS BUTTON ACTION *******************************************************************************************************************

void actionPress(){
  if (window == off) {        // Pantalla desactivada -> Main Window
    window = mainW;
    oled.mainWindow();
  }
  else if (window == mainW) {   // Main Window -> Main Menu
    window = mainM;
    menuItem = 1;
    mainMenu();
  }
  else if (window == mainM) {   // Main Menu -> 
    switch(menuItem) {
      case 1: {
        window = viewD;
        menuItem = 1;
        oled.visualizeData();
        break;
      }
      case 2: {
        window = configM;
        menuItem = 1;
        oled.updateParamsMenu();
        break;
      }
      case 3: {
        window = resetM;
        menuItem = 1;
        oled.resetDataPage();
        break;
      }
      case 4: {
        window = mainM;
        menuItem = 1;
        oled.mainWindow();
        break;
      }
    }
  }
  else if (window == viewD) {   // Visualize Data -> no action
  }
  else if (window == configM) {   // Update Params Menu ->
   switch(menuItem) {
      case 1: {
        window = configFlow;
        menuItem = 1;
        updateFlow();
        break;
      }
      case 2: {
        window = configCond;
        menuItem = 1;
        updateConductivity();
        break;
      }
      case 3: {
        window = configComp;
        menuItem = 1;
        updateComprobations();
        break;
      }
      case 4: {
        window = mainM;
        menuItem = 2;
        mainMenu();
        break;
      }
    }
  }
  else if (window == resetM) {    // Reset Menu ->
    switch(menuItem) {
      case 1: {
        window = mainM;
        menuItem = 3;
        break;
      }
      case 2: {
        window = mainW;
        menuItem = 1;
        resetCounter();
        break;
      }
    }
  }
}

// ROTATE ACTION IN MENU ******************************************************************************************************************

void navigateMenu(){
  rotationEncoder = constrain(rotationEncoder, -1, +1);
  if (rotationEncoder == -1) menuUP();
  else menuDOWN();
  rotationEncoder = 0;
}

void menuUP(){
  if (menuItem == 1) menuItem = itemsPerPage[window];
  else menuItem--;
}

void menuDOWN(){
  if (menuItem == itemsPerPage[window]) menuItem = 1;
  else menuItem++;
}

// ROTATE ACTION IN DATA PAGE *******************************************************************************************************************

void scrollData(){
  
}


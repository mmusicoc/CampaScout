#include "Parameters.hpp"
#include "SerialHandler.hpp"
#include "ControllerStatus.hpp"

ControllerStatus Status;

// SETUP **********************************************************************************************************************************

void setup() {                            // Esta es la rutina estándar que se ejecuta cuando se reinicia el Arduino, es OBLIGATORIA.
  Status.controllerStarter();
  SerialHandler SerialH(Status);          // Llama a la función que inicia el puerto serial de transmisión de datos,
                                          // y si está habilitado el puerto, envía el menú de configuración a la consola serial.
}

// LOOP ***********************************************************************************************************************************

void loop() {                             // Una vez terminada la rutina "setup()", se ejecuta "loop()" indefinidamente hasta que se apague el Arduino.
  delay(DELAY_LOOP);                      // Una pausa de DELAY_LOOP milisegundos para que no haga tantos bucles y gaste menos energía.
  Status.updateStatus();                  // Dependiendo del estado del botón Auto/Manual, ejecuta la función principal de un modo distinto.
}


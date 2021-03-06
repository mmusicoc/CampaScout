#include "0-Params.hpp"
#include "1-Core.hpp"
#include "2-Serial.hpp"

SerialHandler USB;
ControllerCore Core;

void setup() {                            // Esta es la rutina estándar que se ejecuta cuando se reinicia el Arduino, es OBLIGATORIA.
  USB.init();                             // Llama a la función que inicia el puerto serial de transmisión de datos,
  Core.init();
  USB.serialWelcome();                    // Si el puerto está habilitado, envía el menú de configuración a la consola serial.
}

void loop() {                             // Una vez terminada la rutina "setup()", se ejecuta "loop()" indefinidamente hasta que se apague el Arduino.
  if (USB.available()){
    USB.serialWatchDog();                 // Rutina que controla si se ha enviado algo al puerto serial.
    Core.updateSerial(USB);               // Si se ha enviado petición de cambio de algún parámetro, cursa su actualización y guardado en tarjeta SD.
  }
  Core.updateStatus();                    // Dependiendo del estado del botón Auto/Manual, ejecuta la función principal de un modo distinto.
  delay(LOOP_DELAY);                      // Una pausa de DELAY_LOOP milisegundos para que no haga tantos bucles y gaste menos energía.
}

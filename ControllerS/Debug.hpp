#ifndef DEBUG_H
#define DEBUG_H

#define DEBUG(x) if (debug_) {Serial.print(#x); Serial.print(" = "); Serial.println(x);}
/* Macro que imprime por Serial el nombre y valor de la variable x.
   Ejemplo:
     int x = 45;
     DEBUG(x)
   Por serial pondría -> x = 45
*/

#define LIN if (debug_) {Serial.print("Reached line No. "); Serial.println(__LINE__);}
/* Macro que imprime por Serial la línea en la que se encuentra.
   Ejemplo:
      BRK
   Por serial pondría -> Reached line No.15
*/

#define FCN if (debug_) {Serial.print("Executed function \""); Serial.print(__FUNCTION__); Serial.println("\"");}
/* Macro que imprime por Serial la función que está ejecutando en ese momento.
   Ejemplo:
      void funcionA(){
      [...]
      FCN
      }
   Por serial pondría -> Executed function "funcionA"
*/

#define STOP if (debug_) {BRK delay(10); exit(0);}
/* Macro que para instantáneamente la ejecución del programa, pero antes imprime por Serial la línea en la que se encuentra.
   Si se activa un interrupt, puede ejecutarse la función ISR y al terminarla vuelve al reposo.
*/

#endif

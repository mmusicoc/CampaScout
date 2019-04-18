#ifndef DEBUG_H
#define DEBUG_H

#define Sprint(x)       (Serial.print(F(x)))      //Usar solo para cadenas de caracteres ESTÁTICAS Y NO VACÍAS
#define Sprintln(x)     (Serial.println(F(x)))    //Usar solo para cadenas de caracteres ESTÁTICAS Y NO VACÍAS

#define DEBUG(x) {Serial.print(#x); Sprint(" = "); Serial.println(x);}
/* Macro que imprime por Serial el nombre y valor de la variable x.
   Ejemplo:
     int x = 45;
     DEBUG(x)
   Por serial pondría -> x = 45
*/

#define LIN {Serial.print("Reached line No. "); Serial.println(__LINE__);}
/* Macro que imprime por Serial la línea en la que se encuentra.
   Ejemplo:
      BRK
   Por serial pondría -> Reached line No.15
*/

#define FCN {Sprint("Executed function \""); Serial.print(__FUNCTION__); Sprintln("\"");}
/* Macro que imprime por Serial la función que está ejecutando en ese momento.
   Ejemplo:
      void funcionA(){
      [...]
      FCN
      }
   Por serial pondría -> Executed function "funcionA"
*/

#define STOP {LIN delay(10); exit(0);}
/* Macro que para instantáneamente la ejecución del programa, pero antes imprime por Serial la línea en la que se encuentra.
   Si se activa un interrupt, puede ejecutarse la función ISR y al terminarla vuelve al reposo.
*/

#endif

// Debug.h by oscar & mario

#ifndef SRC_DEBUG_H_
#define SRC_DEBUG_H_

/* DEBUG es una macro que imprime por Serial el valor y nombre de una variable
 * Ejemplo:
 *   int x = 45;
 *   DEBUG(x)
 * Por serial pondría "x = 45"
 */

#define DEBUG(x) if(DEB1) {Serial.print(#x); Serial.print(" = "); Serial.println(x);}


/* BRK es una macro que imprime por Serial la linea en la que se encuentra
 * Ejemplo:
 *    if(true) BRK
 *    else BRK
 * Por serial pondría "Code reached line No.2"
 */
#define BRK if(DEB1) {Serial.print("Reached Line #"); Serial.println(__LINE__);}

/* FCN es una macro que imprime por Serial la linea en la que se encuentra
 * Ejemplo:
 *    if(true) BRK
 *    else BRK
 * Por serial pondría "Code reached line No.2"
 */
#define FCN if(DEB1) {Serial.print("Executed function "); Serial.println(__FUNCTION__);}

#endif


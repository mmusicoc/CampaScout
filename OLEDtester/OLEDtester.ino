// Test for minimum program size.



// 0X3C+SA0 - 0x3C or 0x3D

#define I2C_ADDRESS 0x3C
#define OLED_ENABLE     5

#include <SSD1306Ascii.h>

#include <SSD1306AsciiAvrI2c.h>



SSD1306AsciiAvrI2c oled;

//------------------------------------------------------------------------------

void setup() {                

  pinMode(OLED_ENABLE, OUTPUT);
  digitalWrite(OLED_ENABLE, HIGH);

  delay(1000);

  oled.begin(&Adafruit128x64, I2C_ADDRESS);

  oled.setFont(System5x7);

  oled.clear();

  oled.print("Hello world!");

}

//------------------------------------------------------------------------------

void loop() {}

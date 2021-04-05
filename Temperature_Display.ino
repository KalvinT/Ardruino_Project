#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd (0x27,16,2); // set the LCD address to 0x27 for a16 chars and 2 line display

void setup() {
 lcd.begin();

 // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.print("Hello, World");
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
//
}

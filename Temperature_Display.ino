#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

/********************************************************************/
// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2

/********************************************************************/
// Setup a oneWire instance to communicate with any OneWire devices
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

LiquidCrystal_I2C lcd (0x27, 16, 2); // set the LCD address to 0x27 for a16 chars and 2 line display

int relay_pin = 13;
double Tset = 27;
double Tcur = 0;

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

/********************************************************************/
/********************************************************************/
/********************************************************************/
void setup(void)
{
  pinMode(relay_pin, OUTPUT);
  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.print("Hi");
  Serial.begin(9600);
  // start serial port
  Serial.println("Dallas Temperature IC Control Library Demo");
  // Start up the library
  sensors.begin();
}
/********************************************************************/
/********************************************************************/
/********************************************************************/
void loop(void)
{
  Serial.print(" Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperature readings
  Serial.println("DONE");
  Serial.print("Temperature is: ");
  Tcur = sensors.getTempCByIndex(0);
  Serial.print(Tcur); // Why "byIndex"?

  lcd.clear();
  lcd.print("Tcurr = ");
  lcd.print(Tcur);
  lcd.print(" C");
  delay(500);

  //if relay_pin == HIGH then fan is turned on and heater is turned off
  //if relay_pin == LOW then fan is turned off and heater is turned on

  if (Tcur < Tset)
  {
    digitalWrite(relay_pin, LOW);    // turn the LED off by making the voltage LOW
    delay(4000);                       // wait for a second
  }
  else {
    digitalWrite(relay_pin, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(4000);                       // wait for a second
  }
}


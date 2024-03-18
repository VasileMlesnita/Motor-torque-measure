#include "HX711.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

HX711 scale;

uint8_t dataPin = A1;
uint8_t clockPin = A0;
LiquidCrystal_I2C lcd(0x27, 16, 2);
float cuplu = 1; 
String afisareDisplay;

int rpm1 = 60;

float putere = 1;
void setup()
{ 

  //setup pentru display
  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight 

//setup pentru senzorul de greutate
Serial.begin(115200);
Serial.println(_FILE_);
Serial.print("LIBRARY VERSION: ");
Serial.println(HX711_LIB_VERSION);
Serial.println();

scale.begin(dataPin, clockPin);

Serial.print("UNITS: ");
Serial.println(scale.get_units(10));

Serial.println("nEmpty the scale, press a key to continue");
while(!Serial.available());
while(Serial.available()) Serial.read();

scale.tare();
Serial.print("UNITS: ");
Serial.println(scale.get_units(10));


Serial.println("nPut a 1 kg in the scale, press a key to continue");
while(!Serial.available());
while(Serial.available()) Serial.read();

scale.calibrate_scale(100, 1);
Serial.print("UNITS: ");
Serial.println(scale.get_units(10));

Serial.println("nScale is callibrated, press a key to continue");
while(!Serial.available());
while(Serial.available()) Serial.read();

}

void loop()
{
cuplu = scale.get_units(10)*9.81*0.0088;
//partea de display
lcd.setCursor(0,0);
lcd.print("M:" + String(cuplu) + "Nm");
lcd.setCursor(10,0);
lcd.print("n:" + String(rpm1));
lcd.setCursor(0,1);
lcd.print("P:" + String(((2*3.14*rpm1)/60)*cuplu) + "W");
  

//partea de consoala
Serial.println("Cuplu: " + String(cuplu) + " Nm.");
Serial.println(String(scale.get_units(10)));
Serial.println("Puterea " + String(((2*3.14*rpm1)/60)*cuplu) + " W");
}
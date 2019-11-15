#include <LiquidCrystal.h>
 
/*--------Display----------*/
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 5, en = 6, d4 = 7, d5 = 8, d6 = 9, d7 = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

/*----Sound Sensor-----*/
int ledPin = 12;
int sensorPin = 13;
boolean val = 0;

void setup(){
  Serial.begin (9600);

  pinMode(ledPin, OUTPUT);
  pinMode(sensorPin, INPUT);
 
  //Setup of the LCD's number of column and rows
  lcd.begin(16, 2);
  //Displaying welcome to the LCD
  lcd.print("Welcome!");
}
  
void loop (){
  val = digitalRead(sensorPin);
  Serial.println (val);
  // when the sensor detects a signal above the threshold value, LED flashes
  if (val==HIGH) {
	 lcd.clear();
     lcd.setCursor(0,0);//set the cursor at first row
     lcd.print("IntensityHigh:");//Sound Intensity level
     lcd.setCursor(0,1);
     lcd.print(String(val));
     delay(1000);
  }
  else {
    lcd.clear();
    lcd.setCursor(0,0);//set the cursor at first row
    lcd.print("IntensityLow:");//Sound Intensity level
    lcd.setCursor(0,1);
    lcd.print(String(val));
    delay(1000);
  }
}
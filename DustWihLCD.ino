#include <LiquidCrystal.h>

/*--------Display----------*/
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 5, en = 6, d4 = 7, d5 = 8, d6 = 9, d7 = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

/*-------Dust-------*/
int measurePin = A5;
int ledPower = 13;

unsigned int samplingTime = 280;
unsigned int deltaTime = 40;
unsigned int sleepTime = 9680;

float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;

void setup(){
  Serial.begin(9600);
  pinMode(ledPower,OUTPUT);

  //Setup of the LCD's number of column and rows
  lcd.begin(16, 2);
  //Displaying welcome to the LCD
  lcd.print("Welcome!");
}

void loop(){
  digitalWrite(ledPower,LOW);
  delayMicroseconds(samplingTime);

  voMeasured = analogRead(measurePin);

  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH);
  delayMicroseconds(sleepTime);

  calcVoltage = voMeasured*(5.0/1024);
  dustDensity = 0.17*calcVoltage-0.1;

  if ( dustDensity < 0)
  {
    dustDensity = 0.00;
  }

  /** Displaying sensor information to LCD **/
  lcd.clear();//clearing everything written previously from the lcd
  //initial cursos is set at first row
  lcd.print("RwSigVal(0-1023)");//As the lcd has 16 column in each row, so we need to pass a string of 16 charachter, anything beyond that won't be displayed.
  lcd.setCursor(0,1);//set the cursor at the second row to display something in the 2nd row
  lcd.print(String(voMeasured));
  delay(1000);//1000 mili sec delay to display the voMeasured for 1000ms time.

  lcd.clear();
  lcd.setCursor(0,0);//set the cursor at first row
  lcd.print("Voltage:");
  lcd.setCursor(0,1);
  lcd.print(String(calcVoltage));
  delay(1000);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Dust Density:");
  lcd.setCursor(0,1);//
  lcd.print(String(dustDensity));
  delay(1000);
}

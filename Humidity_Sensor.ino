// C++ code
//
#include <LiquidCrystal.h>

int tempPin = A0; 
int tempInput; 
double temp; 
int motorPin = 3;
int redPin = 4;
int bluePin = 5;
int greenPin = 6;
int buzzerPin = 2;

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
const int contrast = 7;

void setup()
{  
  pinMode(motorPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);  
  Serial.begin(9600);
  
  analogWrite(contrast, 100);
  lcd.begin(16, 2);
}

void loop()
{
	tempInput = analogRead(A0); 
	temp = (double)tempInput / 1024; 
	temp = (temp * 5 - 0.5) * 100; 
	Serial.print("Current Temperature: ");
	Serial.println(temp);
    lcd.setCursor(0, 0);
    lcd.print("Temperature: " + String(temp) + " C");
  	
  if (temp <= 0) {
  	digitalWrite(redPin, 0);
    digitalWrite(greenPin, 0);
    digitalWrite(bluePin, 252);
    digitalWrite(motorPin, LOW);
	tone(buzzerPin, 1000);
    delay(1000);
    noTone(buzzerPin);
    delay(1000);    lcd.setCursor(0,1);
    lcd.print("DANGER: TOO COLD");
  }
  if (temp >= 0 && temp <= 45) {
  	digitalWrite(redPin, 0);
    digitalWrite(greenPin, 252);
    digitalWrite(bluePin, 0);
    digitalWrite(motorPin, LOW);
	noTone(buzzerPin);
    lcd.setCursor(0, 1);
	lcd.print("                     ");
  }
  if (temp > 45) {
  	digitalWrite(redPin, 252);
    digitalWrite(greenPin, 0);
    digitalWrite(bluePin, 0);
    digitalWrite(motorPin, HIGH);
    tone(buzzerPin, 1000);
    delay(1000);
    noTone(buzzerPin);
    delay(1000);
    lcd.setCursor(0, 1);
	lcd.print("DANGER: TOO HOT");
  }
}
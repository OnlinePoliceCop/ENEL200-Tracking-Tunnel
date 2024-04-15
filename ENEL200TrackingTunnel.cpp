
#include "LowPower.h"
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);

const int camPin = 8;
const int sensPin = 3;
const int lcdPin = 2;
int count = 0;
bool flagCNT = false;
bool flagLCD = false;
bool animal = false;
//--------------------------------------------------------------
void isr() {
  flagCNT = true;
}
//--------------------------------------------------------------
void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(sensPin, INPUT);
  pinMode(lcdPin, INPUT_PULLUP);
  pinMode(camPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(sensPin), isr, FALLING);
  attachInterrupt(digitalPinToInterrupt(lcdPin), lcd_printer, LOW);
}
//--------------------------------------------------------------
void lcd_printer() {
  flagLCD = true;
}
//--------------------------------------------------------------
void loop() {
  if (digitalRead(sensPin) == HIGH) {
    animal = false;
  } else if (digitalRead(sensPin) == LOW) {
    animal = true;
  }

  if (flagCNT == true && animal == true) {
    count++;
    digitalWrite(camPin, HIGH);
    delay(30);
    digitalWrite(camPin, LOW);
    flagCNT = false;
  }
  if (flagLCD == true) {
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Count: ");
    lcd.print(count);
    delay(1000);
    flagLCD = false;
  }
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
}

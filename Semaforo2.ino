//www.elegoo.com
//2016.12.9

/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 7
 * LCD Enable pin to digital pin 8
 * LCD D4 pin to digital pin 9
 * LCD D5 pin to digital pin 10
 * LCD D6 pin to digital pin 11
 * LCD D7 pin to digital pin 12
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>
//led
#define RED 6
#define GREEN 5
#define RED2 1
#define GREEN2 0
//bottoni
#define BUTTONPIT1 2
#define BUTTONPIT2 3
#define BUTTONTIMEPLUS 4

long timestamp_ingresso1;
double counter1;
bool ingresso1 = false;
long timestamp_ingresso2;
double counter2;
bool ingresso2 = false;
int durata = 10000; //durata pitstop in ms

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RED2, OUTPUT);
  pinMode(GREEN2, OUTPUT);
  pinMode(BUTTONPIT1, INPUT_PULLUP);  
  pinMode(BUTTONPIT2, INPUT_PULLUP);
  pinMode(BUTTONTIMEPLUS, INPUT_PULLUP);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, HIGH);
  // Print a message to the LCD.
  delay(500);
  lcd.print("System Ready.");
  delay(500);
  lcd.clear();  
}

void loop() {

  if (digitalRead(BUTTONPIT1) == LOW && ingresso1 == false) {
    timestamp_ingresso1 = millis();
    ingresso1 = true;
    analogWrite(RED, 255);
    analogWrite(GREEN, 0);
    lcd.setCursor(0,0);
    lcd.print("1CHIUSA");
  }

  if (ingresso1 == true && (millis() - timestamp_ingresso1) <= durata) {
    if ((millis() - timestamp_ingresso1) % 100 == 0) {
      lcd.setCursor(0,1);
      counter1 = (durata - (millis() - timestamp_ingresso1)) / 100;
      lcd.print(counter1/10, 1);
    }
  }

  if (ingresso1 == true && (millis() - timestamp_ingresso1) > durata) {
    ingresso1 = false;
    lcd.setCursor(0,0);
    lcd.print("1aperta");
    analogWrite(RED, 0);
    analogWrite(GREEN, 255);
  }

  if (digitalRead(BUTTONPIT2) == LOW && ingresso2 == false) {
    timestamp_ingresso2 = millis();
    ingresso2 = true;
    analogWrite(RED2, 255);
    analogWrite(GREEN2, 0);
    lcd.setCursor(9,0);
    lcd.print("2CHIUSA");
  }

  if (ingresso2 == true && (millis() - timestamp_ingresso2) <= durata) {
    if ((millis() - timestamp_ingresso2) % 100 == 0) {
      lcd.setCursor(9,1);
      counter2 = (durata - (millis() - timestamp_ingresso2)) / 100;
      lcd.print(counter2/10, 1);
    }
  }

  if (ingresso2 == true && (millis() - timestamp_ingresso2) > durata) {
    ingresso2 = false;
    lcd.setCursor(9,0);
    lcd.print("2aperta");
    analogWrite(RED2, 0);
    analogWrite(GREEN2, 255);
  }

  if (digitalRead(BUTTONTIMEPLUS) == LOW) {
    lcd.clear();
    lcd.print("PitLane CHIUSA");
    analogWrite(RED, 255);
    analogWrite(GREEN, 0);
    analogWrite(RED2, 255);
    analogWrite(GREEN2, 0);
  }
  
}


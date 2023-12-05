/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

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
//buttons
#define BUTTONPIT1 2
#define BUTTONPIT2 3
#define BUTTONCLOSEPIT 4
//#define BUTTONOPENPIT --
//#define 4 buttons for adding and removing penalty time for each pitbox stall

long timestamp_entry1;
double counter1;
bool entry1 = false;
long timestamp_entry2;
double counter2;
bool entry2 = false;
int lenght = 10000; //pitstop lenght in ms
bool override = false;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RED2, OUTPUT);
  pinMode(GREEN2, OUTPUT);
  pinMode(BUTTONPIT1, INPUT_PULLUP);  
  pinMode(BUTTONPIT2, INPUT_PULLUP);
  pinMode(BUTTONCLOSEPIT, INPUT_PULLUP);
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
//if button pit 1 pressed then get a timestamp and turn red indicator for pitlane 1
  if (digitalRead(BUTTONPIT1) == LOW && entry1 == false) {
    timestamp_entry1 = millis();
    entry1 = true;
    analogWrite(RED, 255);
    analogWrite(GREEN, 0);
    lcd.setCursor(0,0);
    lcd.print("1CLOSE");
  }
//pitstop counter for box 1
  if (entry1 == true && (millis() - timestamp_entry1) <= lenght) { //TODO: modify to account for added penalty time
    if ((millis() - timestamp_entry1) % 100 == 0) {
      lcd.setCursor(0,1);
      counter1 = (lenght - (millis() - timestamp_entry1)) / 100;
      lcd.print(counter1/10, 1);
    }
  }
//when time is up reset everything unless pit entry is closed (override)
  if (entry1 == true && (millis() - timestamp_entry1) > lenght ) { //TODO: modify to account for added penalty time
    entry1 = false;
    //penalty1 = 0; (reset penalty when pitstop1 time is up)
    if (override == true) { //if pitlane is closed (override) then set the lane green for 1 second to give start to the driver and then set everything to red
      lcd.setCursor(0,0);
      lcd.print("PitLane CLOSED");
      analogWrite(RED, 0); //TWEAK: if we use different pins for controlling the lights at the entrance and at the exit we can keep the entrance lights red when there is override, and only flash green the exit lights to give start to the stopped driver to resume race
      analogWrite(GREEN, 255);
      delay(1000);
      analogWrite(RED, 255);
      analogWrite(GREEN, 0);
      analogWrite(RED2, 255);
      analogWrite(GREEN2, 0);
    } else {
      lcd.setCursor(0,0);
      lcd.print("1 open");
      analogWrite(RED, 0);
      analogWrite(GREEN, 255);
    }
  }

  if (digitalRead(BUTTONPIT2) == LOW && entry2 == false) {
    timestamp_entry2 = millis();
    entry2 = true;
    analogWrite(RED2, 255);
    analogWrite(GREEN2, 0);
    lcd.setCursor(9,0);
    lcd.print("2CLOSE");
  }

  if (entry2 == true && (millis() - timestamp_entry2) <= lenght) { //TODO: modify to account for added penalty time
    if ((millis() - timestamp_entry2) % 100 == 0) {
      lcd.setCursor(9,1);
      counter2 = (lenght - (millis() - timestamp_entry2)) / 100;
      lcd.print(counter2/10, 1);
    }
  }

  if (entry2 == true && (millis() - timestamp_entry2) > lenght) { //TODO: modify to account for added penalty time
    entry2 = false;
    //penalty2 = 0; (reset penalty when pitstop2 time is up)
    if (override == true) { //if pitlane is closed (override) then set the lane green for 1 second to give start to the driver and then set everything to red
      lcd.setCursor(9,0);
      lcd.print("PitLane CLOSED");
      analogWrite(RED2, 0);
      analogWrite(GREEN2, 255);
      delay(1000);
      analogWrite(RED, 255);
      analogWrite(GREEN, 0);
      analogWrite(RED2, 255);
      analogWrite(GREEN2, 0);
    } else {
      lcd.setCursor(9,0);
      lcd.print("2 open");
      analogWrite(RED2, 0);
      analogWrite(GREEN2, 255);
    }
  }

  if (digitalRead(BUTTONCLOSEPIT) == LOW) {
    lcd.clear();
    lcd.print("PitLane CLOSED");
    override = true;
    analogWrite(RED, 255);
    analogWrite(GREEN, 0);
    analogWrite(RED2, 255);
    analogWrite(GREEN2, 0);
  }

  /*if (digitalRead(BUTTONOPENPIT) == LOW) {
    lcd.clear();
    lcd.print("PitLane OPEN");
    override = false;
    analogWrite(RED, 0);
    analogWrite(GREEN, 255);
    analogWrite(RED2, 0);
    analogWrite(GREEN2, 255);
  }*/

  //TODO: adding support for penalty time (two buttons per pitbox, +5 seconds and -5 seconds)
  //if button penalty1plus pressed -> penalty1 = penalty1 + 5000;
  //if button penalty1minus pressed -> penalty1 = penalty1 - 5000;
  //if penalty1 < 0 then penalty1 = 0;

  //if button penalty2plus pressed -> penalty2 = penalty2 + 5000;
  //if button penalty2minus pressed -> penalty2 = penalty2 - 5000;
  //if penalty2 < 0 then penalty2 = 0;
  
}


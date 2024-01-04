// Description: This is the main file for the project.

#include "mfshield.h"

using namespace MF_Shield;

void setup()
{
  /** Serial **/
  Serial.begin(9600);
  Serial.println("MF Shield Test");
  Serial.flush();

  /** Who is this? **/
  whoIam();

  /** LEDs **/
  pinMode(ledD1, OUTPUT);
  pinMode(ledD2, OUTPUT);
  pinMode(ledD3, OUTPUT);
  pinMode(ledD4, OUTPUT);

  /** Button style Switches **/
  pinMode(swS1, INPUT);
  pinMode(swS2, INPUT);
  pinMode(swS3, INPUT);

  /** Lil Blue Potentiometer **/
  pinMode(potA0, INPUT);

  /** Buzzer **/
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, HIGH);

  /** Display Pins - define pins 4, 7, 8 as OUTPUT **/
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop()
{
}

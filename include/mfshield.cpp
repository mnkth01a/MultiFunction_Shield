
#include <MultiFunction_Shield.h>

using namespace MF_Shield;

MFShield::MF_Shield()
{
   // Constructor
}

MFShield::~MF_Shield()
{
   // Destructor
}

void MFShield::begin()
{
   /** Serial **/
   Serial.begin(BAUD_RATE);
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

void MFShield::whoIam()
{
   // Display the microcontroller's information to the serial monitor
   Serial.println("Device Name: " + String(DEVICE_NAME));
   Serial.println("CPU: " + String(__AVR_ARCH__));
   Serial.println("Clock Speed: " + String(F_CPU));
   Serial.println("ARDUINO: " + String(ARDUINO));
   Serial.println("ARDUINO_AVR_UNO: " + String(ARDUINO_AVR_UNO));
   Serial.println();
   Serial.flush();
}

void MFShield::blink()
{
   // check if it's time to blink the LED; that is, if the difference
   // between the current time and last time you blinked the LED is bigger than
   // the interval at which you want to blink the LED.
   currentTime = millis();
   if (currentTime - previousblinkTime >= blinkInterval)
   {
      // save the last time you blinked the LED
      previousblinkTime = currentTime;

      // if the LED is off turn it on and vice-versa:
      ledState = !ledState;
      digitalWrite(ledD1, ledState);
   }
}

void MFShield::fade()
{
   // check to see if it's time to fade the LED; that is, if the difference
   // between the current time and last time you faded the LED is bigger than
   // the interval at which you want to fade the LED.
   currentTime = millis();
   if (currentTime - previousfadeTime >= fadeInterval)
   {
      // save the last time you blinked the LED
      previousfadeTime = currentTime;

      // if the LED is off turn it on and vice-versa:
      ledState = !ledState;
      digitalWrite(ledD2, ledState);
   }
}

bool MFShield::button_debounce(boolean last)
{
   boolean current = digitalRead(swS1);
   if (last != current)
   {
      delay(30);
      current = digitalRead(swS1);
   }
   return current;
}

void MFShield::tellProcessing()
{
   // check if button is pressed and if so, send a message to the serial monitor
   buttonState = button_debounce(lastButtonState);
   if (buttonState)
   {
      Serial.println("Button Pressed");
      Serial.flush();
   }
   lastButtonState = buttonState;
}

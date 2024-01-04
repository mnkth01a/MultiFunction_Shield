
#include <MultiFunction_Shield.h>

using namespace MF_Shield;

void MF_Shield::whoIam()
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

void MF_Shield::blink()
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

void MF_Shield::fade()
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

bool MF_Shield::button_debounce(boolean last)
{
   boolean current = digitalRead(swS1);
   if (last != current)
   {
      delay(30);
      current = digitalRead(swS1);
   }
   return current;
}

void MF_Shield::tellProcessing()
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

#ifndef mfshield_h
#define mfshield_h

#include <Arduino.h>

namespace MF_Shield

{
   /** Constants **/
   const int DEVICE_ID = 0x0a; // Change this to the ID of this device
   const char DEVICE_NAME[] = "MultiFunctionShield";
   const int BAUD_RATE = 9600;

   /** Multi-Function Shield Variables **/
   const int ledD1 = 13; // LED1 connected to digital pin 13
   const int ledD2 = 12; // LED2 connected to digital pin 12
   const int ledD3 = 11; // LED3 connected to digital pin 11
   const int ledD4 = 10; // LED4 connected to digital pin 10

   const int swS1 = A1; // Switch A1 connected to analog pin A1
   const int swS2 = A2; // Switch A2 connected to analog pin A2
   const int swS3 = A3; // Switch A3 connected to analog pin A3

   const int LM35 = A4; // LM35 connected to analog pin A4

   const int potPinA0 = A0; // Potentiometer connected to analog pin A0

   /** 7-Segment Display Variables **/
   const int latchPin = 4; // Latch connected to digital pin 4
   const int clockPin = 7; // Clock connected to digital pin 7
   const int dataPin = 8; // Data connected to digital pin 8

   unsigned char Dis_table[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99,
                                0x92, 0x82, 0xf8, 0x80, 0x90}; // This table defines the 7 segments of the display, 0x is not used here.  00 = all segments ON, FF = all segments OFF, 0x7f is used for the decimal point.

   unsigned char Dis_buf[] = {0xf1, 0xf2, 0xf4, 0xf8}; // this table sets a selector for what digit to display.  0xf1 = digit 1, 0xf2 = digit 2, etc.

   unsigned char disbuf[] = {0, 0, 0, 0}; // this is the buffer that holds the data to be sent to the display

   /** Buzzer Variables **/
   const int buzzerPin = 3; // Buzzer connected to digital pin 3

   /* Free pins (PWM) **/
   const int PWM5 = 5; // PWM pin 5
   const int PWM6 = 6; // PWM pin 6
   const int PWM9 = 9; // PWM pin 9
   const int PWMA5 = A5; // PWM pin A5

   /** Logic Variables **/
   int SUM = 0;


   bool ledState;
   bool lastButtonState;
   bool buttonState;

   byte cycleCount = 0;

   unsigned long currentTime = 0;
   unsigned long previousblinkTime = 0;
   unsigned long previousfadeTime = 0;
   unsigned long previouscycleTime = 0;


   /** Functions **/
   void whoIam()
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

   bool button_debounce(boolean last)
   {
      boolean current = digitalRead(swS1);
      if (last != current)
      {
         delay(30);
         current = digitalRead(swS1);
      }
      return current;
   }

   void tellProcessing()
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

   void blink()
   {
      // check if it's time to blink the LED; that is, if the difference
      // between the current time and last time you blinked the LED is bigger than
      // the interval at which you want to blink the LED.
      currentTime = millis();
      if (currentTime - previousblinkTime >= 1000)
      {
         previousblinkTime = currentTime;
         // if the LED is off turn it on and vice-versa:
         ledState = !ledState;
         digitalWrite(ledD1, ledState);
      }
   }

   void fade()
   {
      // fade in from min to max in increments of 5 points:
      for (int fadeValue = 0; fadeValue <= 255; fadeValue += 5)
      {
         // sets the value (range from 0 to 255):
         analogWrite(ledD2, fadeValue);
         // wait for 30 milliseconds to see the dimming effect
         delay(30);
      }

      // fade out from max to min in increments of 5 points:
      for (int fadeValue = 255; fadeValue >= 0; fadeValue -= 5)
      {
         // sets the value (range from 0 to 255):
         analogWrite(ledD2, fadeValue);
         // wait for 30 milliseconds to see the dimming effect
         delay(30);
      }
   }
} // namespace MF_Shield
#endif // mfshield_h
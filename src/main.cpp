// Description: This is the main file for the project.

#include <Arduino.h>
#include <Wire.h>
#include "mfshield.h"

MFShield mfshield;
Buzzer buzzer;
LED led;

int i = 0;

void setup()
{
   /** Serial **/
   Serial.begin(BAUD_RATE);
   Serial.println("Serial Monitor Started\n");
   Serial.flush();

   /** Who is this? **/
   mfshield.whoIam();

   buzzer.buzz(5, 1000);

   /** LEDs **/
   led.led_off(1);
   led.led_off(2);
   led.led_off(3);
   led.led_off(4);
}

void loop()
{
   for (int i = 1; i < 5; i++)
   {
      led.led_toggle(i);
      delay(500);
   };

   for (int j = 4; j > 0; j--)
   {
      led.led_toggle(j);
      delay(500);
   };

   //buzzer.buzz(50, 1000);

   // for (int k = 1; k < 256; k++)
   // {
   //    Serial.println("Fade = " + String(k));
   //    led.led_fade(1, k);
   //    delay(100);
   // }

   // for (int l = 255; l > 0; l--)
   // {
   //    Serial.println("Fade = " + String(l));
   //    led.led_fade(1, l);
   //    delay(100);
   // }
}

// Description: This is the main file for the project.

#include <Arduino.h>
#include <Wire.h>
#include "mfshield.h"

MFShield mfshield;
Buzzer buzzer;
LED led;
Potentiometer pot;
SSD ssd;
Button button1;
Button button2;
Button button3;

int i = 0;
int val = 0;

void setup()
{
   /** Serial **/
   Serial.begin(BAUD_RATE);
   Serial.println("Serial Monitor Started\n");
   Serial.flush();

   /** Who is this? **/
   mfshield.whoIam();

   buzzer.buzz_on(5, 1000);

   /** LEDs **/
   led.led_off(1);
   led.led_off(2);
   led.led_off(3);
   led.led_off(4);
}

void loop()
{
   for (int i = 2; i < 5; i++)
   {
      led.led_toggle(i);
      delay(500);
   };

   for (int j = 4; j > 1; j--)
   {
      led.led_toggle(j);
      delay(500);
   };

   val = pot.read();
   //Serial.println("Potentiometer Value = " + String(val));
   delay(300);

   val /= 17;
   //Serial.println("Buzzer Buzzing at " + String(val) + " Hz");
   //buzzer.buzz_on(int(val), 500);

   val = button1.read(swS1);
   if (val == 1)
   {
      Serial.println("Button 1 Pressed");
      led.led_on(1);
   }
   else
   {
      led.led_off(1);
   }
}


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
// }

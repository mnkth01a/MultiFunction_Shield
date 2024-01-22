// Description: This is the main file for the project.

#include <Arduino.h>
#include <Wire.h>
#include "mfshield.h"

MFShield mfshield;
Buzzer buzzer;
LED led;
Potentiometer pot;
SSD ssd;
Button button1(swS1);
Button button2(swS2);
Button button3(swS3);

int i = 0;
int val = 0;

volatile bool glob_button_toggle = false;

void button_ISR();

void setup()
{
   /** Serial **/
   Serial.begin(BAUD_RATE);
   Serial.println("Serial Monitor Started\n");
   Serial.flush();

   /** Who is this? **/
   mfshield.whoIam();

   /** Buttons **/
   //button2.watch();
   attachInterrupt(digitalPinToInterrupt(2), button_ISR, FALLING);

   /** LEDs **/
   led.led_off(1);
   led.led_off(2);
   led.led_off(3);
   led.led_off(4);

   buzzer.buzz_on(5, 1000);
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
   // Serial.println("Potentiometer Value = " + String(val));
   delay(300);

   val /= 17;
   // Serial.println("Buzzer Buzzing at " + String(val) + " Hz");
   // buzzer.buzz_on(int(val), 500);

   val = button1.read();
   if (val == 1)
   {
      Serial.println("Button 1 Pressed");
      led.led_on(1);
   }
   else
   {
      led.led_off(1);
   };

   if (glob_button_toggle == true)
   {
      Serial.println("Button 2 Toggled");
   };
}


void button_ISR()
{
   // toggle the button interrupt
   glob_button_toggle = !glob_button_toggle;
};


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

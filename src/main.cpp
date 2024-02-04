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

int value = 0;
int seg = 0;
int dis = 0;

bool glob_button_toggle = false;

void setup()
{
   /** Serial **/
   Serial.begin(BAUD_RATE);
   Serial.println("Serial Monitor Started\n");
   Serial.flush();

   /** Who is this? **/
   mfshield.whoIam();

   /** Buttons **/
   // button2.watch();

   /** LEDs **/
   led.led_off(1);
   led.led_off(2);
   led.led_off(3);
   led.led_off(4);

   /** SSD **/
   ssd.display(0xf1, 0xc0);
   ssd.display(0xf2, 0xc0);
   ssd.display(0xf4, 0xc0);
   ssd.display(0xf8, 0xc0);

   /** Buzzer **/
   buzzer.buzz_on(5, 1000);
}

void loop()
{
   /****************************************************************/
   /****************************************************************/
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
   /****************************************************************/
   /****************************************************************/
   ssd.Dis_data[0] = 5;
   ssd.Dis_data[1] = 9;
   ssd.Dis_data[2] = 6;
   ssd.Dis_data[3] = 8;

   if (seg > 3)
   {
      seg = 0;
   };

   ssd.display(ssd.Segment_Select[seg], ssd.Dis_Table[ssd.Dis_data[seg]]);
   delay(250);

   seg++;
   // ssd.auto_count_up();
   /****************************************************************/
   /****************************************************************/
   value = pot.read();
   // Serial.println("Potentiometer Value = " + String(value));
   delay(300);

   value /= 17;
   // Serial.println("Buzzer Buzzing at " + String(value) + " Hz");
   // buzzer.buzz_on(int(value), 500);
   /****************************************************************/
   /****************************************************************/
   // ssd.auto_count_down();
   /****************************************************************/
   /****************************************************************/
   value = button1.read();
   if (value == 1)
   {
      Serial.println("Button 1 Pressed");
      led.led_on(1);
   }
   else
   {
      led.led_off(1);
   };

   value = button2.read();
   if (value == 1)
   {
      Serial.println();
      Serial.println("Button 2 Pressed");
      button2.toggle(glob_button_toggle);
      Serial.println("Global button toggled = " + String(glob_button_toggle));
      Serial.println("Button 2 Toggled");
      Serial.println();
   };
   /****************************************************************/
   /****************************************************************/
}

// End of File
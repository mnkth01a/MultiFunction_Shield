// Description: This is the main file for the project.

#include "mfshield.h"

MFShield mfs;

void setup()
{
   /** Serial **/
   Serial.begin(BAUD_RATE);
   Serial.println("MF Shield Test");
   Serial.flush();

   /** Who is this? **/
   mfs.whoIam();
}

void loop()
{

}

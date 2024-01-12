// Description: This is the main file for the project.

#include "mfshield.h"

void setup()
{
   /** Serial **/
   Serial.begin(BAUD_RATE);
   Serial.println("MF Shield Test");
   Serial.flush();

   /** Who is this? **/
   mfshield.whoIam();
}

void loop()
{

}

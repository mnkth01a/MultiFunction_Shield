
#include "mfshield.h"

using namespace MF_Shield;

MFShield::MFShield()
{
   // Constructor
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
}

MFShield::~MFShield()
{
   // Destructor
}

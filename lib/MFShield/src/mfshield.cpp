
#include "mfshield.h"

MFShield::MFShield()
{
   // Constructor
   /** LEDs **/
   pinMode(_ledD1, OUTPUT);
   pinMode(_ledD2, OUTPUT);
   pinMode(_ledD3, OUTPUT);
   pinMode(_ledD4, OUTPUT);

   /** Button style Switches **/
   pinMode(_swS1, INPUT);
   pinMode(_swS2, INPUT);
   pinMode(_swS3, INPUT);

   /** Lil Blue Potentiometer **/
   pinMode(_potA0, INPUT);

   /** Buzzer **/
   pinMode(_buzzerPin, OUTPUT);
   digitalWrite(_buzzerPin, HIGH);
}

MFShield::~MFShield()
{
   // Destructor
}

void MFShield::whoIam(void)
{
   // Display the microcontroller's information to the serial monitor
   Serial.println("Device Name: " + String(DEVICE_NAME));
   Serial.println("CPU: " + String(__AVR_ARCH__));
   Serial.println("Clock Speed: " + String(F_CPU));
   Serial.println("ARDUINO: " + String(ARDUINO));
   Serial.println("ARDUINO_AVR_UNO: " + String(ARDUINO_AVR_UNO));
   Serial.println();
   Serial.flush();
};


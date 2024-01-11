#ifndef mfshield_h
#define mfshield_h

#include <Arduino.h>
#include <Wire.h>

/******************************************************************************/
/*                                                                            */
/*                           Namespace MF_Shield                              */
/*                                                                            */
/******************************************************************************/
namespace MF_Shield
{
   class MFShield
   {
   private:
      /** Constants **/
      const char DEVICE_NAME[32] = "MultiFunctionShield";
      const int DEVICE_ID = 0x0a; // Change this to the ID of this device
      const int BAUD_RATE = 9600;

      unsigned char Dis_table[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99,
                                     0x92, 0x82, 0xf8, 0x80, 0x90}; // This table defines the 7 segments of the display, 0x is not used here.  00 = all segments ON, FF = all segments OFF, 0x7f is used for the decimal point.

      unsigned char Dis_buf[4] = {0xf1, 0xf2, 0xf4, 0xf8}; // this table sets a selector for what digit to display.  0xf1 = digit 1, 0xf2 = digit 2, etc.

      unsigned char disbuf[4] = {0, 0, 0, 0}; // this is the buffer that holds the data to be sent to the display

      const int swS2 = A2; // Switch A2 connected to analog pin A2
      const int swS3 = A3; // Switch A3 connected to analog pin A3

      const int LM35 = A4; // LM35 connected to analog pin A4

      const int potA0 = A0; // Potentiometer connected to analog pin A0

      /** 7-Segment Display Variables **/
      const int latchPin = 4; // Latch connected to digital pin 4
      const int clockPin = 7; // Clock connected to digital pin 7
      const int dataPin = 8;  // Data connected to digital pin 8

      /** Buzzer Variables **/
      const int buzzerPin = 3; // Buzzer connected to digital pin 3

      /* Servos pins (PWM's) **/
      const int Servo1 = 5;  // Servo in 5
      const int Servo2 = 6;  // Servo in 6
      const int Servo3 = 9;  // Servo in 9
      const int Servo4 = A5; // Servo in A5

      /** IR Receive Socket Declaration **/
      const int IR_RECV_SOCKET = 2;

      /************************************************************************/
      /*                                                                      */
      /*                         Logic Variables                              */
      /*                                                                      */
      /************************************************************************/
      int SUM = 0;

      int Flag_up = 1;
      int Flag_up1 = 1;

      bool ledState;
      bool lastButtonState;
      bool buttonState;

      byte cycleCount = 0;

      unsigned long currentTime = 0;
      unsigned long previousblinkTime = 0;
      unsigned long previousfadeTime = 0;
      unsigned long previouscycleTime = 0;

   public:
      /************************************************************************/
      /*                                                                      */
      /*                   Function Declarations                              */
      /*                                                                      */
      /************************************************************************/
      void begin();
      void whoIam();
      void blink();
      void fade();
      bool button_debounce(boolean last);
      void tellProcessing();
   };
} // namespace MF_Shield
#endif // mfshield_h

#ifndef mfshield_h
#define mfshield_h

#include <Arduino.h>
#include <Wire.h>

const char DEVICE_NAME[] = "MultiFunctionShield";
const int DEVICE_ID = 0x0a; // Change this to the ID of this device
const int BAUD_RATE = 9600;

/** LED Variables **/
const int ledD1 = 13; // LED D1 connected to digital pin 13
const int ledD2 = 12; // LED D2 connected to digital pin 12
const int ledD3 = 11; // LED D3 connected to digital pin 11
const int ledD4 = 10; // LED D4 connected to digital pin 10

/** Switches, Sensors and Potentiometer Variables **/
const int swS1 = A1; // Switch A1 connected to analog pin A1
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
/*                      MFShield Class Declaration                      */
/*                                                                      */
/************************************************************************/
class MFShield
{
private:
   /************************************************************************/
   /*                                                                      */
   /*                         Private Variables                            */
   /*                                                                      */
   /************************************************************************/
   /** Constants **/
   int _ledD1 = ledD1;
   int _ledD2 = ledD2;
   int _ledD3 = ledD3;
   int _ledD4 = ledD4;

   int _swS1 = swS1;
   int _swS2 = swS2;
   int _swS3 = swS3;

   int _LM35 = LM35;

   int _potA0 = potA0;

   int _buzzerPin = buzzerPin;

   int _latchPin = latchPin;
   int _clockPin = clockPin;
   int _dataPin = dataPin;

   int _Servo1 = Servo1;
   int _Servo2 = Servo2;
   int _Servo3 = Servo3;
   int _Servo4 = Servo4;

   int _IR_RECV_SOCKET = IR_RECV_SOCKET;

public:
   /************************************************************************/
   /*                                                                      */
   /*            Common Function Declarations                              */
   /*                                                                      */
   /************************************************************************/
   MFShield();
   ~MFShield();

   void whoIam(void);
}; // class MFShield

extern MFShield mfshield;


/************************************************************************/
/*                                                                      */
/*                   Servo Class Declaration                            */
/*                                                                      */
/************************************************************************/
class Servo
{
private:
   int _pin;
   int _angle;

public:
   Servo(int pin)
   {
      _pin = pin;
      pinMode(_pin, OUTPUT);
   }

   ~Servo()
   {
      // Destructor
   }

   void write(int angle)
   {
      _angle = angle;
      analogWrite(_pin, _angle);
   }
}; // class Servo

/************************************************************************/
/*                                                                      */
/*                   7-Segment Display Class Declaration                */
/*                                                                      */
/************************************************************************/
class SevenSegmentDisplay
{
private:
   int _latchPin = latchPin;
   int _clockPin = clockPin;
   int _dataPin = dataPin;
   int _digit;
   int _number;

   unsigned char Dis_table[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99,
                                  0x92, 0x82, 0xf8, 0x80, 0x90}; // This table defines the 7 segments of the display, 0x is not used here.  00 = all segments ON, FF = all segments OFF, 0x7f is used for the decimal point.

   unsigned char Dis_buf[4] = {0xf1, 0xf2, 0xf4, 0xf8}; // this table sets a selector for what digit to display.  0xf1 = digit 1, 0xf2 = digit 2, etc.

   unsigned char disbuf[4] = {0, 0, 0, 0}; // this is the buffer that holds the data to be sent to the display

public:
   SevenSegmentDisplay(int latchPin, int clockPin, int dataPin, int digit)
   {
      _latchPin = latchPin;
      _clockPin = clockPin;
      _dataPin = dataPin;
      _digit = digit;
      pinMode(_latchPin, OUTPUT);
      pinMode(_clockPin, OUTPUT);
      pinMode(_dataPin, OUTPUT);
   }

   SevenSegmentDisplay(int digit)
   {
      _digit = digit;
      pinMode(_latchPin, OUTPUT);
      pinMode(_clockPin, OUTPUT);
      pinMode(_dataPin, OUTPUT);
   }

   ~SevenSegmentDisplay()
   {
      // Destructor
   }

   void write(int digit, int number)
   {
      _digit = digit;
      if (_digit > 3)
      {
         _digit = 3;
      }
      else if (_digit < 0)
      {
         _digit = 0;
      }

      _number = number;
      if (_number > 9)
      {
         _number = 9;
      }
      else if (_number < 0)
      {
         _number = 0;
      }

      digitalWrite(_latchPin, LOW);
      shiftOut(_dataPin, _clockPin, MSBFIRST, Dis_table[_number]);
      shiftOut(_dataPin, _clockPin, MSBFIRST, Dis_buf[_digit]);
      digitalWrite(_latchPin, HIGH);
   }
}; // class SevenSegmentDisplay

/************************************************************************/
/*                                                                      */
/*                      Buzzer Class Declaration                        */
/*                                                                      */
/************************************************************************/
class Buzzer
{
private:
   int _pin;
   int _frequency;
   unsigned long _duration;

public:
   Buzzer(int pin)
   {
      _pin = pin;
      pinMode(_pin, OUTPUT);
   }

   ~Buzzer()
   {
      // Destructor
   }

   // frequency (in hertz) and duration (in milliseconds).
   void buzz(int frequency, unsigned long duration)
   {
      _frequency = frequency;
      _duration = duration;
      tone(_pin, _frequency, _duration);
   }
}; // class Buzzer

/************************************************************************/
/*                                                                      */
/*                      */
/*                                                                      */
/************************************************************************/

#endif // mfshield_h

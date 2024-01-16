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
   int _swS1 = swS1;
   int _swS2 = swS2;
   int _swS3 = swS3;

   int _LM35 = LM35;

   int _potA0 = potA0;

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

/************************************************************************/
/*                                                                      */
/*                         LED Class Declaration                        */
/*                                                                      */
/************************************************************************/
class LED
{
private:
   int _led;
   int _ledD1;
   int _ledD2;
   int _ledD3;
   int _ledD4;

public:
   LED();
   ~LED();

   void led_on(int);
   void led_off(int);
   void led_toggle(int);
   void led_fade(int, int);
}; // class LED

/************************************************************************/
/*                                                                      */
/*                   7-Segment Display Class Declaration                */
/*                                                                      */
/************************************************************************/
class SSD
{
private:
   int _latchPin = latchPin;
   int _clockPin = clockPin;
   int _dataPin = dataPin;
   int _digit;
   int _number;

   unsigned char Dis_number[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99,
                                   0x92, 0x82, 0xf8, 0x80, 0x90}; // This table defines the 7 segments of the display, 0x is not used here.  00 = all segments ON, FF = all segments OFF, 0x7f is used for the decimal point.

   unsigned char Dis_digit[4] = {0xf1, 0xf2, 0xf4, 0xf8}; // this table sets a selector for what digit to display.  0xf1 = digit 1, 0xf2 = digit 2, etc.

   unsigned char Dis_data[4] = {0, 0, 0, 0}; // this is the buffer that holds the data to be sent to the display

public:
   SSD();
   ~SSD();

   // digit (0-3) and number (0-9)
   void write(int, int);
}; // class SevenSegmentDisplay

extern SSD ssd;

/************************************************************************/
/*                                                                      */
/*                      Potentiometer Class Declaration                 */
/*                                                                      */
/************************************************************************/
class Potentiometer
{
private:
   int _potPin;
   int _value;

public:
   Potentiometer(int);
   ~Potentiometer();

   int read(void);
}; // class Potentiometer

/************************************************************************/
/*                                                                      */
/*                      Buzzer Class Declaration                        */
/*                                                                      */
/************************************************************************/
class Buzzer
{
private:
   int _buzzerPin;
   int _frequency;
   int _duration;
   int _period;
   int _buzzerFreq;

public:
   Buzzer();
   ~Buzzer();

   // frequency (in hertz) and duration (in milliseconds).
   void buzz(int, int);
}; // class Buzzer

/************************************************************************/
/*                                                                      */
/*                   Servo Class Declaration                            */
/*                                                                      */
/************************************************************************/
class Servo
{
private:
   int _servoPin;
   int _angle;

public:
   Servo(int);
   ~Servo();

   void write(int);
}; // class Servo

/************************************************************************/
/*                                                                      */
/*                      */
/*                                                                      */
/************************************************************************/

#endif // mfshield_h

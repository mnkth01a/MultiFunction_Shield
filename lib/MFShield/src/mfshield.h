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
const int swS1 = 15; // Switch A1 connected to analog pin A1
const int swS2 = 16; // Switch A2 connected to analog pin A2
const int swS3 = 17; // Switch A3 connected to analog pin A3

const int LM35 = A4; // LM35/DS1820 temp sensor module connected to analog pin A4

const int potA0 = A0; // Potentiometer connected to analog pin A0

/** 7-Segment Display Variables **/
#define latchPin 4; // Latch connected to digital pin 4
#define clockPin 7; // Clock connected to digital pin 7
#define dataPin 8;  // Data connected to digital pin 8

/** Buzzer Variables **/
const int buzzerPin = 3; // Buzzer connected to digital pin 3

/* Servos pins (PWM's) **/
const int Servo1 = 5;  // Servo in 5
const int Servo2 = 6;  // Servo in 6
const int Servo3 = 9;  // Servo in 9
const int Servo4 = A5; // Servo in A5

/** IR Receive Socket Declaration **/
const int IR_RECV_SOCKET = 2;

// volatile bool glob_button_toggle;

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
/*                      Button Class Declaration                        */
/*                                                                      */
/************************************************************************/
class Button
{
private:
   volatile int _pin_addr;

public:
   Button(const int &);
   ~Button();

   // @param pin_addr: swS1, swS2, swS3
   int read();
   void watch();
   void unwatch();
   void toggle(bool &);
}; // class Button

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
   int _latchPin;
   int _clockPin;
   int _dataPin;
   int i, j, k, l;

   int Flag_up;
   int Flag_up1;

   const unsigned char SEG_OFF = 0xff; // this is the value to turn off all segments

   const unsigned char SEG_ON = 0x00; // this is the value to turn on all segments

public:
   const unsigned char Dis_Table[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99,
                                        0x92, 0x82, 0xf8, 0x80, 0x90}; // This table defines the 7 segments of the display, 0x is not used here.  00 = all segments ON, FF = all segments OFF, 0x7f is used for the decimal point.

   const unsigned char Segment_Select[4] = {0xf1, 0xf2, 0xf4, 0xf8}; // this table sets a selector for what digit to display.  0xf1 = digit 1, 0xf2 = digit 2, etc.
   
   unsigned char Dis_data[4] = {0, 0, 0, 0};                         // this is the buffer that holds the data to be sent to the display

   SSD();
   ~SSD();

   void auto_count_up();
   void auto_count_down();
   void display(char, char);
   void display_buffer();
}; // class SevenSegmentDisplay

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
   Potentiometer();
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
   void buzz_on(int, int);
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

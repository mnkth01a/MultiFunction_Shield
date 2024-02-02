
#include "mfshield.h"

/************************************************************************/
/*                                                                      */
/*                      MFShield Class Definition                       */
/*                                                                      */
/************************************************************************/
MFShield::MFShield(){
    // Constructor
};

MFShield::~MFShield(){
    // Destructor
};

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

/************************************************************************/
/*                                                                      */
/*                       Button Class Definition                        */
/*                                                                      */
/************************************************************************/
Button::Button(const int &pin_addr)
{
   // Constructor

   _pin_addr = pin_addr;

   /** Button style Switches **/
   pinMode(_pin_addr, INPUT);
};

Button::~Button()
{
   // Destructor
   detachInterrupt(digitalPinToInterrupt(_pin_addr));
};

int Button::read() // pin_addr: swS1, swS2, swS3
{
   // int _state = 0;
   int _state = digitalRead(_pin_addr); // _state is the state of the switch at pin_addr.

   return !_state; // I had to invert the logic for the switches to work intuitively.
};

void Button::watch(){
    // todo attachInterrupt() will not work here. Uno uses pins 2 and 3 for interrupts, and the buttons are on pins A1, A2, and A3.  Need to develop a workaround.

    // start ISR to initialize the button interrupt
    // attachInterrupt(digitalPinToInterrupt(_pin_addr), button_ISR, FALLING);
};

void Button::unwatch()
{
   // stop ISR to initialize the button interrupt
   detachInterrupt(digitalPinToInterrupt(_pin_addr));
};

void Button::toggle(bool &_button_toggle)
{
   _button_toggle = !_button_toggle;
};

/************************************************************************/
/*                                                                      */
/*                         LED Class Declaration                        */
/*                                                                      */
/************************************************************************/
LED::LED()
{
   // Constructor
   _ledD1 = ledD1;
   _ledD2 = ledD2;
   _ledD3 = ledD3;
   _ledD4 = ledD4;

   /** LEDs **/
   pinMode(_ledD1, OUTPUT);
   pinMode(_ledD2, OUTPUT);
   pinMode(_ledD3, OUTPUT);
   pinMode(_ledD4, OUTPUT);
};

LED::~LED(){
    // Destructor
};

// You have to set the pins to LOW to turn on the LEDs
void LED::led_on(int led)
{
   _led = led;
   if (_led == 1)
   {
      digitalWrite(_ledD1, LOW);
   }
   else if (_led == 2)
   {
      digitalWrite(_ledD2, LOW);
   }
   else if (_led == 3)
   {
      digitalWrite(_ledD3, LOW);
   }
   else if (_led == 4)
   {
      digitalWrite(_ledD4, LOW);
   }
};

// You have to set the pins to HIGH to turn off the LEDs
void LED::led_off(int led)
{
   _led = led;
   if (_led == 1)
   {
      digitalWrite(_ledD1, HIGH);
   }
   else if (_led == 2)
   {
      digitalWrite(_ledD2, HIGH);
   }
   else if (_led == 3)
   {
      digitalWrite(_ledD3, HIGH);
   }
   else if (_led == 4)
   {
      digitalWrite(_ledD4, HIGH);
   }
};

// You have to toggle the pins to toggle the LEDs (Duh!)
void LED::led_toggle(int ledDx)
{
   _led = ledDx;
   if (_led == 1)
   {
      _led = digitalRead(_ledD1);
      digitalWrite(_ledD1, !_led);
   }
   else if (_led == 2)
   {
      _led = digitalRead(_ledD2);
      digitalWrite(_ledD2, !_led);
   }
   else if (_led == 3)
   {
      _led = digitalRead(_ledD3);
      digitalWrite(_ledD3, !_led);
   }
   else if (_led == 4)
   {
      _led = digitalRead(_ledD4);
      digitalWrite(_ledD4, !_led);
   }
};

void LED::led_fade(int ledDx, int fade)
{
   _led = ledDx;
   if (_led == 1)
   {
      analogWrite(_ledD1, fade);
      delay(10);
   }
   else if (_led == 2)
   {
      analogWrite(_ledD2, fade);
      delay(10);
   }
   else if (_led == 3)
   {
      analogWrite(_ledD3, fade);
      delay(10);
   }
   else if (_led == 4)
   {
      analogWrite(_ledD4, fade);
      delay(10);
   }
};

/************************************************************************/
/*                                                                      */
/*                   7-Segment Display Class Definition                 */
/*                                                                      */
/************************************************************************/
SSD::SSD()
{
   i = 0;
   j = 9999;
   k = 0;

   _dataPin = dataPin;
   _clockPin = clockPin;
   _latchPin = latchPin;

   pinMode(_latchPin, OUTPUT);
   pinMode(_clockPin, OUTPUT);
   pinMode(_dataPin, OUTPUT);

   if (__AVR_ARCH__ != 2)
   {
      Serial.println("This library only supports AVR architecture.");
      Serial.println("Exiting...");
      exit(2);
   };
};

SSD::~SSD(){
    // Destructor
};

void SSD::auto_count_up()
{
   // Count up from 0 to 999
   i++;

   if (i > 3)
   {
      i = 0;
   };

   display(Segment_Select[i], SEG_ON);
   delay(100);

   Serial.println("i = " + String(i));
};

void SSD::auto_count_down()
{
   // Count down from 999 to 0
   j--;

   if (j <= 0)
   {
      j = 9999;
   };

   Dis_data[0] = j / 1000;
   Dis_data[1] = j % 1000;
   Dis_data[2] = j % 100;
   Dis_data[3] = j % 10;
   display_buffer();
   delay(100);
};

void SSD::display(char Segment_no, char hexvalue)
{
   // Send value to the four displays
   for (k = 0; k <= 3; k++)
   {
      digitalWrite(_latchPin, LOW);
      shiftOut(_dataPin, _clockPin, MSBFIRST, hexvalue);
      shiftOut(_dataPin, _clockPin, MSBFIRST, Segment_no);
      digitalWrite(_latchPin, HIGH);
      delay(2);
   }
};

void SSD::display_buffer()
{
   // Send value to the four displays
   for (k = 0; k <= 3; k++)
   {
      digitalWrite(_latchPin, LOW);
      shiftOut(_dataPin, _clockPin, MSBFIRST, Dis_Table[Dis_data[k]]);
      shiftOut(_dataPin, _clockPin, MSBFIRST, Segment_Select[k]);
      digitalWrite(_latchPin, HIGH);
      delay(2);
   }
};

/************************************************************************/
/*                                                                      */
/*                  Potentiometer Class Definition                      */
/*                                                                      */
/************************************************************************/
Potentiometer::Potentiometer()
{
   _potPin = potA0;
   pinMode(_potPin, INPUT);
};

Potentiometer::~Potentiometer(){
    // Destructor
};

int Potentiometer::read(void)
{
   _value = analogRead(_potPin);
   return _value;
};

/************************************************************************/
/*                                                                      */
/*                      Buzzer Class Definition                         */
/*                                                                      */
/************************************************************************/
Buzzer::Buzzer()
{
   _buzzerPin = buzzerPin;
   pinMode(_buzzerPin, OUTPUT);
   digitalWrite(_buzzerPin, HIGH); // turn off buzzer
};

Buzzer::~Buzzer(){
    // Destructor
};

// frequency (in hertz) and duration (in milliseconds).
void Buzzer::buzz_on(int frequency, int duration)
{
   //
   _frequency = frequency;
   _duration = duration;
   _buzzerFreq = map(_frequency, 0, 60, 255, 0);
   _period = 1000000 / _frequency;

   analogWrite(_buzzerPin, _buzzerFreq);
   delay(_duration);
   digitalWrite(_buzzerPin, HIGH);
};

/************************************************************************/
/*                                                                      */
/*                   Servo Class Definition                             */
/*                                                                      */
/************************************************************************/
Servo::Servo(int &pin)
{
   if (goodPin(pin))
   {
      _servoPin = pin;
      pinMode(_servoPin, OUTPUT);
   }
   else
   {
      exit(1);
   }
};

Servo::~Servo(){
    // Destructor
};

bool Servo::goodPin(int &_servoPin)
{
   if (_servoPin != Servo1Pin5 &&
       _servoPin != Servo2Pin6 &&
       _servoPin != Servo3Pin9 &&
       _servoPin != Servo4PinA5)
   {
      Serial.println("Invalid Pin");
      Serial.println("Please use one of the following pins: 5, 6, 9, 19 or A5");
      Serial.println("Exiting...");

      return false;
   }
   else
   {
      Serial.println();
      Serial.println("Valid Pin");
      return true;
   }
};

int Servo::setAO(int &_angle)
{
   int _val = map(_angle, 0, 180, 0, 255);
   return _val;
};

void Servo::write(int &_angle)
{
   int _val = setAO(_angle);
   analogWrite(_servoPin, _val);
};

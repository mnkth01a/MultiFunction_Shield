
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
Button::Button()
{
   // Constructor

   /** Button style Switches **/
   pinMode(_swS1, INPUT);
   pinMode(_swS2, INPUT);
   pinMode(_swS3, INPUT);
};

Button::~Button(){
    // Destructor
};

int Button::read(int sw)
{
   int _state = 0;
   int _sw = sw;

   _state = digitalRead(_sw);

   // I had to invert the logic for the switches to work intuitively.
   return !_state;
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
   pinMode(_latchPin, OUTPUT);
   pinMode(_clockPin, OUTPUT);
   pinMode(_dataPin, OUTPUT);
};

SSD::~SSD(){
    // Destructor
};

// digit (0-3) and number (0-9)
void SSD::display()
{
   // Send value to the four displays
   for (i = 0; i < 4; i++)
   {
      digitalWrite(_latchPin, LOW);
      shiftOut(_dataPin, _clockPin, MSBFIRST, Dis_table[Dis_data[i]]);
      shiftOut(_dataPin, _clockPin, MSBFIRST, Dis_buffer[i]);
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
Servo::Servo(int pin)
{
   _servoPin = pin;
   pinMode(_servoPin, OUTPUT);
};

Servo::~Servo(){
    // Destructor
};

void Servo::write(int angle)
{
   _angle = angle;
   analogWrite(_servoPin, _angle);
};

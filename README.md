# Building a libary for the Arduino capatabilty Multi-Function Shield

Like the Velleman VMA209, or the Arduino Multi-Function shields.

## Getting Started

I found that the I/O pins on the VMA209 were not labeled correctly, and the documentation was not very good.  So I decided to create a library to make it easier to use the shield.

The first thing I've discovered is that the I/O logic has to be inverted in order for the logic to work correctly.  Like the button state is opposite of what you would expect.  So I've created a function to invert the logic for you.

### Issues

lib/MFShield/src/mfshield.cpp: In member function 'void Button::watch()':
lib/MFShield/src/mfshield.cpp:61:73: error: invalid use of non-static member function 'void Button::button_ISR()'
    attachInterrupt(digitalPinToInterrupt(_pin_addr), button_ISR, FALLING);
                                                                         ^
In file included from lib/MFShield/src/mfshield.cpp:2:0:
lib/MFShield/src/mfshield.h:86:9: note: declared here
    void button_ISR()
         ^~~~~~~~~~
*** [.pio/build/uno/lib891/MFShield/mfshield.cpp.o] Error 1


mfshield.cpp.o (symbol from plugin): In function `MFShield::MFShield()':
(.text+0x0): multiple definition of `glob_button_toggle'
.pio/build/uno/src/main.cpp.o (symbol from plugin):(.text+0x0): first defined here
collect2: error: ld returned 1 exit status
*** [.pio/build/uno/firmware.elf] Error 1


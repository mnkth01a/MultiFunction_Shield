# Building a libary for the Arduino capatabilty Multi-Function Shield

Like the Velleman VMA209, or the Arduino Multi-Function shields.

## Getting Started

I found that the I/O pins on the VMA209 were not labeled correctly, and the documentation was not very good.  So I decided to create a library to make it easier to use the shield.

The first thing I've discovered is that the I/O logic has to be inverted in order for the logic to work correctly.  Like the button state is opposite of what you would expect.  So I've created a function to invert the logic for you.

### Issues

The push buttons on the Multi-Function shield are on pins A1, A2, and A3.  The attached interrupt service routines use pins 2, and 3 on the Arduino Uno, so you can't use the push buttons with the interrupt service routines.


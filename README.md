# Building a libary for the Arduino capatabilty Multi-Function Shield

Like the Velleman VMA209, or the Arduino Multi-Function shields.

## Getting Started

I found that the I/O pins on the VMA209 were not labeled correctly, and the documentation was not very good.  So I decided to create a library to make it easier to use the shield.

The first thing I've discovered is that the I/O logic has to be inverted in order for the logic to work correctly.  Like the button state is opposite of what you would expect.  So I've created a function to invert the logic for you.

### Issues

The push buttons on the Multi-Function shield are on pins A1, A2, and A3.  The attached interrupt service routines use pins 2, and 3 on the Arduino Uno, so you can't use the push buttons with the interrupt service routines.

The 4 digit seven segment display does not function correctly.  It does not retain the previous value when you change to the next digit.  So, when you want to display "1234", it will display the one, but then changes to the next digit and displays the "2", but the "1" is no longer displayed.  And that cycles like that in both directions.  I have not found a way to show all four digits at the same time.

Also, the b segment comes on anytime the segment is active and a segment is active.  So, if you want to display a "5", the b segment is also active making it look like an "9".  The same is true for the "6" which looks like an "8".  I even spent some time trying to figure out how to turn off the b segment, but I was not successful.

The potentiometer is of the multiturn type that is great for fine tuning, but is not very good for sweeping the value.  

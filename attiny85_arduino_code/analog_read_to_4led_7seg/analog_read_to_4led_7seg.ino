/*
	Basic usage example

	Demonstrated some of the basic functionality of the library. Initialize the display, set the backlight brightness, print some text, count from 0 to 100 and print on display and blink some text.

  Note: make sure to set your serial monitor to line end: NEW LINE!

	The circuit:
  * connect TM1637 pin CLK to Arduino pin D4
  * connect TM1637 pin DIO to Arduino pin D5
  * connect TM1637 pin Vcc to Arduino pin 5V
  * connect TM1637 pin GND to Arduino pin GND

	Created 25 September 2015
	By Bram Harmsen

	https://github.com/bremme/arduino-tm1637

*/

// include the SevenSegmentTM1637 library
#include "SevenSegmentTM1637.h"

/* initialize global TM1637 Display object
*  The constructor takes two arguments, the number of the clock pin and the digital output pin:
* SevenSegmentTM1637(byte pinCLK, byte pinDIO);
*/
const byte PIN_CLK = 3;   // define CLK pin (any digital pin)
const byte PIN_DIO = 4;   // define DIO pin (any digital pin)
SevenSegmentTM1637    display(PIN_CLK, PIN_DIO);
// run setup code
void setup() {
  display.begin();            // initializes the display
  display.setBacklight(100);  // set the brightness to 100 %
  display.print("ON");      // display INIT on the display
  delay(100);        // delay in between reads for stability
};

// run loop (forever)
void loop() {
  int sensorValue = analogRead(A1);
  display.print(sensorValue);                   // display loop counter
  delay(100);        // delay in between reads for stability
};

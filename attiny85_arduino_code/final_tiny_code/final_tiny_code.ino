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
//const byte PIN_CLK = 4;   // define CLK pin (any digital pin)
//const byte PIN_DIO = 5;   // define DIO pin (any digital pin)
const byte PIN_CLK = 3;   // define CLK pin (any digital pin)
const byte PIN_DIO = 4;   // define DIO pin (any digital pin)
SevenSegmentTM1637    display(PIN_CLK, PIN_DIO);

unsigned long readingSensorWait;
unsigned long warmupWait;
unsigned long timeReset = 0;
unsigned long timeSensor = 0;

int breathTesting = 0;
int drunkLevel;  // Highest score
int splashScreen = 1;
int mainBreath = 0;
int warmupNumber;
int minReading;
int maxReading;
//int firstRun = 1;
int startUp;

// Button stuff
const int button = 0; // Button set to pin 5
long time_button = 0; // the last time the output pin was toggled
long debounce = 50; // the debounce time, increase if the output flickers
int reading_button; // the current reading from the input pin
int previous_button = HIGH; // the previous reading from the input pin

// run setup code
void setup() {
//  Serial.begin(9600);         // initializes the Serial connection @ 9600 baud
  display.begin();            // initializes the display
  display.setBacklight(100);  // set the brightness to 100 %
  display.print("ON");      // display INIT on the display
//  delay(1000);                // wait 1000 ms
  pinMode(button, INPUT); // Set the button as input
  digitalWrite(button, HIGH); // initiate the internal pull up resistor
};

// run loop (forever)
void loop() {
  int sensorValue = analogRead(A1);
//  int sensorValue = analogRead(A0);
//  Serial.println(sensorValue);
//  display.print(sensorValue);                   // display loop counter
//  delay(100);        // delay in between reads for stability

//  display.print("LOOP");                // display LOOP on the display
//  delay(1000);                          // wait 1000 ms
//  display.print("COUNTING SOME DIGITS");// print COUNTING SOME DIGITS
//  display.clear();                      // clear the display
//  for (uint8_t i=0; i < 100; i++) {     // loop from 0 to 100
//    display.print(i);                   // display loop counter
//    delay(100);                         // wait 100 ms
//  };
  display.clear();                      // clear the display

  // startup code
  if (splashScreen == 1)
  {

  while (startUp < 5) 
  {
 // ------------- Debound code button green start code -------------
    reading_button = digitalRead(button);

    if (reading_button == HIGH && previous_button == LOW && millis() - time_button > debounce) 
    { 
      time_button = millis(); 
      // Do something here
//      Serial.println("button press");
//      breathTesting = 1;
      startUp = 5;
      warmupNumber = 100;
    }
      previous_button = reading_button;
     
 // -------------- Debound code button green end code -------------
    while (millis() >= warmupWait)
    {
      display.print("drnk");      // display INIT on the display
      startUp += 1;
      warmupWait += 1000;
    }
  }

    if(warmupNumber <= 99)
    {
    display.clear();                      // clear the display
        display.print(warmupNumber); // print SUCC for success
//      delay(600);        // delay in between reads for stability
      delay(850);        // delay in between reads for stability
        warmupNumber++;
    } 
    else
    {
      int sensorValue = analogRead(A1);
      display.print("Done"); // print SUCC for success
      delay(100);        // delay in between reads for stability
      splashScreen = 0;
      mainBreath = 1;
//      firstRun = 0;
      minReading = sensorValue;
//      maxReading = minReading+300;
      maxReading = minReading+600;
    }

  }

  if (mainBreath == 1)
  {
//    int sensorValue = analogRead(A0);
//    Serial.println(sensorValue);
//    Serial.println(minReading);
//    Serial.println(maxReading);
//    display.print(sensorValue);                   // display loop counter
//    Serial.println("main");
//    drunkLevel = map(sensorValue, minReading, maxReading,0, 10);
    display.print(drunkLevel);                   // display loop counter
    delay(100);        // delay in between reads for stability

  }

//  if (breathTesting == 1 && firstRun == 0)
  if (breathTesting == 1)
  {
      while(millis() <= readingSensorWait) 
      {

//        int sensor = analogRead(analogPin); // Reads the analogPin
//        Serial.println("blow");
        display.print("blow");                   // display loop counter
        int sensorValue = analogRead(A1);
        drunkLevel = map(sensorValue, minReading, maxReading,0, 10);
//        lcd.setCursor(30, 2); // Set cursor postion
//        lcd.setFontSize(FONT_SIZE_MEDIUM); // Set text size
//        lcd.println("Blow now"); // Print to screen
      }
    breathTesting = 0;
    mainBreath = 1;
  }
//  else if (breathTesting == 1 && firstRun == 1)
//  {
//      Serial.println("start skip");
//      minReading = sensorValue;
//      maxReading = minReading+500;
//      firstRun = 0;
//      mainBreath = 1;
//  }

 // ------------- Debound code button green start code -------------
  reading_button = digitalRead(button);

  if (reading_button == HIGH && previous_button == LOW && millis() - time_button > debounce) 
  { 
    time_button = millis(); 
    // Do something here
//    Serial.println("button press");
    readingSensorWait = millis() + 3000;
    timeReset = millis();
    timeSensor = millis(); 
    mainBreath = 0;
    breathTesting = 1;
//    splashScreen = 0;
  }
  previous_button = reading_button;
   
 // -------------- Debound code button green end code -------------
};

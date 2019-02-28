// 25 February 2019
// Code by Andrew Brodsky for Team Muon Cat – ASEN 1400
//
// This program is adapted from the TwoPortReceive example found at 
// https://www.arduino.cc/en/Tutorial/TwoPortReceive, which is in the public domain.


// Include the SoftwareSerial library in this sketch and create three objects, one for each
// Geiger counter.
#include <SoftwareSerial.h>

SoftwareSerial topCounter(2,3);
SoftwareSerial midCounter(4,5);
SoftwareSerial botCounter(6,7);

// Declare some global vars:
unsigned long startTime = 0;
int cycles = 0;

String topVal;
String midVal;
String botVal;

void setup() {
  // Start the good ol' serial port
  Serial.begin(9600);

  while (!Serial) {
  // Wait for hardware serial port to connect. This step is recommended in the TwoPortReceive example.
  }

  // Start our virtual serial ports
  topCounter.begin(9600);
  midCounter.begin(9600);
  botCounter.begin(9600);

  // Wait a full second (reasoning explained below)
  delay(1000);
}

void loop() {
  // The goal of this code is to see how fast an Arduino can read from 3 virtual serial ports and 
  // then write data to its hardware serial port (which writes data to the OpenLog). This sketch
  // will calculate the frequency in Hz at which the Arduino is able to accomplish this task.

  // Recall that we waited for a full second in setup; this ensures that this if statement will be triggered during the
  // first run through loop().
  if((millis()-startTime)>=1000){

    // Output how many cycles the Arduino was able to do in 1 second:
    Serial.println();
    Serial.println( String( "Cycles: "+String(cycles) ) );

    // Reset the cycle counter and start time:
    cycles = 0;
    startTime = millis(); // get the time
  }

  // Listen on all of the virtual serial ports and get the first byte that comes in (should be a 1 or 
  // a 0, depending on whether or not a particle was detected).
  topCounter.listen();
  topVal = topCounter.read();

  midCounter.listen();
  midVal = midCounter.read();

  botCounter.listen();
  botVal = botCounter.read();

  Serial.print(String(topVal+", "+midVal+", "+botVal+"; "));
  
  // Increment the number of cycles and do it all again!
  cycles += 1;

}

// 25 February 2019
// Code by Andrew Brodsky for Team Muon Cat – ASEN 1400
//
// This program is adapted from the DS1307_RTC_Demo.ino included 
// in SparkFun's SparkFunDS1307RTC library and released under the MIT License.

#include <SparkFunDS1307RTC.h> // make sure you have this library installed!
#include <Wire.h>

// Declare some global vars:
unsigned long startTime = 0;
int cycles = 0;

void setup() 
{
  // Use the serial monitor to view time/date output
  Serial.begin(9600);
  
  // Initialize the RTC library
  rtc.begin();

  // Wait a full second (reasoning explained below)
  delay(1000);
}

void loop() 
{

  // Recall that we waited for a full second in setup; this ensures that this if statement will be triggered during the
  // first run through loop(). The statement measures how many loops the Arduino is able to do in 1 second.
  if((millis()-startTime)>=1000){

    // Output how many cycles the Arduino was able to do in 1 second:
    Serial.println();
    Serial.println( String( "Cycles: "+String(cycles) ) );

    // Reset the cycle counter and start time:
    cycles = 0;
    startTime = millis(); // get the time
  }
  
  // Call rtc.update() to get the latest date/time values for all the library's return functions.
  rtc.update();

  // Now read off the time and date! (this part wholeheartedly stolen from SparkFun's example)
  
  // Print hour
  Serial.print(String(rtc.hour()) + ":");
  
  // Print leading '0' for minute if necessary
  if (rtc.minute() < 10) Serial.print('0');
  // Print minute
  Serial.print(String(rtc.minute()) + ":"); 

  // Print leading '0' for second if necessary
  if (rtc.second() < 10) Serial.print('0');
  // Print second
  Serial.print(String(rtc.second()));

  Serial.print(" "); // add space before date
  // print the full date! (in day/month/year format)
  Serial.print(String(rtc.date()) + "/" + String(rtc.month()) + "/" + String(rtc.year()) + " ");

  // Increment the number of cycles and do it all again!
  cycles += 1;
  
}

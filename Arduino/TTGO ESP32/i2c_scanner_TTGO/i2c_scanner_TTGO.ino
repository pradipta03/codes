 // --------------------------------------
// i2c_scanner
// This code is modified by Pradipta on May 2022 to fit esp32 TTGO 1.14inch 
// display to utilize the vibrant lcd screen on it.
//
// Version 1
//    This program (or code that looks like it)
//    can be found in many places.
//    For example on the Arduino.cc forum.
//    The original author is not know.
// Version 2, Juni 2012, Using Arduino 1.0.1
//     Adapted to be as simple as possible by Arduino.cc user Krodal
// Version 3, Feb 26  2013
//    V3 by louarnold
// Version 4, March 3, 2013, Using Arduino 1.0.3
//    by Arduino.cc user Krodal.
//    Changes by louarnold removed.
//    Scanning addresses changed from 0...127 to 1...119,
//    according to the i2c scanner by Nick Gammon
//    http://www.gammon.com.au/forum/?id=10896
// Version 5, March 28, 2013
//    As version 4, but address scans now to 127.
//    A sensor seems to use address 120.
// Version 6, November 27, 2015.
//    Added waiting for the Leonardo serial communication.

// This sketch tests the standard 7-bit addresses
// Devices with higher bit address might not be seen properly.

//

#include <Wire.h> // for i2c libary
#include <TFT_eSPI.h> // for the specific lcd library on ttgo esp32
#include <SPI.h>


TFT_eSPI tft = TFT_eSPI();                   // Invoke custom library with default width and height

unsigned long drawTime = 0;

void setup()
{
  Wire.begin();

  Serial.begin(9600);
  while (!Serial);             // Leonardo: wait for serial monitor
  Serial.println("I2C Scanner");
  
  
  tft.begin();
  tft.setRotation(1);
}


void loop()
{
  byte error, address;
  int nDevices;


  // a background colour defined
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0, 1);
  tft.setTextColor(TFT_WHITE,TFT_BLACK);  tft.setTextSize(2);
  tft.println("I2C Scanner");
  delay(1000);
  
  Serial.println("Scanning...");
  tft.println(" "); // to inlcude one blank line
  tft.println("Scanning...");
  
  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      tft.println("I2C device found at address 0x");
      if (address<16) 
        Serial.print("0");
        tft.print("0");
      Serial.print(address,HEX);
      tft.print(address,HEX);
      Serial.println("  !");
      tft.println("  !");

      nDevices++;
    }
    else if (error==4) 
    {
      Serial.print("Unknown error at address 0x");
      tft.println("Unknown error at address 0x");
      if (address<16) 
        Serial.print("0");
        tft.println("0");
      Serial.println(address,HEX);
      tft.println(address,HEX);
    }    
  }
  if (nDevices == 0){
    Serial.println("No I2C devices found\n");
    tft.println("No I2C devices found\n");
  }
  else{
    Serial.println("done\n");
    tft.println("done\n");

  }


  delay(5000);           // wait 5 seconds for next scan
}

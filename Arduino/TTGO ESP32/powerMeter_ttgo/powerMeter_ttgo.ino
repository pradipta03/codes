/* Power meter with INA260 sensor and 
 *  ttgo esp32 with 1.14 inch lcd
 */

#include <Adafruit_INA219.h>
#include <Wire.h>
#include <SPI.h>

float avgCurrent = 0, avgVoltage = 0, avgPower = 0;
int sampleNum = 30; // number of smaples

#include <TFT_eSPI.h> // for the specific lcd library on ttgo esp32
TFT_eSPI tft = TFT_eSPI();                   // Invoke custom library with default width and height


Adafruit_INA219 ina219 = Adafruit_INA219();

void setup() {
  Serial.begin(115200);
  // Wait until serial port is opened
  while (!Serial) { delay(10); }

  //  Initiate tft module
  tft.begin();
  tft.setRotation(1);

  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0, 1);
  tft.setTextColor(TFT_WHITE,TFT_BLACK);  tft.setTextSize(2);

  Serial.println("Adafruit INA219 Test");
  tft.println("Adafruit INA219 Test");

  if (!ina219.begin()) {
    Serial.println("Couldn't find INA219 chip");
    tft.println("Couldn't find INA219 chip");
    while (1);
  }
  Serial.println("Found INA219 chip");
  tft.println("Found INA219 chip");
}

void loop() {

  for (int i =1; i<=sampleNum; i++){
    avgCurrent = avgCurrent + ina219.getCurrent_mA();
    avgVoltage = avgVoltage + ina219.getBusVoltage_V();
    avgPower = avgPower + ina219.getPower_mW();
  }

   avgCurrent = avgCurrent/sampleNum;
   avgVoltage = avgVoltage/sampleNum;
   avgPower = avgPower/sampleNum;
  
  Serial.print("Current: ");
//  Serial.print(ina219.readCurrent());
  Serial.print(avgCurrent);
  Serial.println(" mA");

  Serial.print("Bus Voltage: ");
//  Serial.print(ina219.readBusVoltage());
  Serial.print(avgVoltage);
  Serial.println(" mV");

  Serial.print("Power: ");
//  Serial.print(ina219.readPower());
  Serial.print(avgPower);
  Serial.println(" mW");

  Serial.println();

  /* Print on the tft display*/

  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0, 1);
  tft.setTextColor(TFT_WHITE,TFT_BLACK);  tft.setTextSize(2);

  tft.print("Current: ");
//  tft.print(ina219.readCurrent());
  tft.print(avgCurrent);
  tft.println(" mA");

  tft.print("Bus Voltage: ");
//  tft.print(ina219.readBusVoltage());
  tft.print(avgVoltage);   
  tft.println(" mV");

  tft.print("Power: ");
//  tft.print(ina219.readPower());
  tft.print(avgPower);
  tft.println(" mW");

  tft.println();

  
  delay(1000);
}

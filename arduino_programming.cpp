#Arduino programming in C/C++ language to cover following three objectives:
#To measure values of currents & voltages with a reasonable sampling rate in-order to record
#required Maximas and Minimas
#Save measured values
#Communicate (send) two types of data, namely saved data & live data. Saved data: Send values
#to memory module, to be stored. Live data: Send live data to the module.

#This code is designed to: acquire data, save data and send it to live stream in the main loop
#When user sends '6' from Bluetooth serial via mobile app, code sends saved file to mobile for
#processing and then again goes back into the main loop


#include <Adafruit_ADS1015.h>
#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <stdio.h>
#include <OneWire.h>
#include <DallasTemperature.h>

SoftwareSerial BTserial(1, 0); // RX | TX
String BT_input;
#define ONE_WIRE_BUS 5
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
File dataFile;
Adafruit_ADS1115 ads;
const float VE = 12.29 / 3.376;
const int chipSelect = 4;
int s = 0;
unsigned long start;
unsigned long stop2;
float V;
String comp = "";
float multiplier = 0.125F; //0.1875F; /* ADS1115 @ +/- 6.144V gain (16-bit results) */

void setup() {
  Serial.begin(9600);
  ads.setGain(GAIN_ONE);
  ads.begin();
  while (!Serial)
    ;
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1)
      ;
  }
}

void loop() {
  comp = "";
  sensors.setWaitForConversion(false); // makes it async 0
  sensors.requestTemperatures();       // 2
  sensors.setWaitForConversion(true); // 0
  comp += String(sensors.getTempCByIndex(0)) + ";"; // 27
  comp += String((ads.readADC_Differential_0_1()) * multiplier * 1.25) + ";"; // 9
  comp += String(((ads.readADC_Differential_2_3()) * multiplier / 1000) * VE) + ";"; // 8
  dataFile = SD.open("DataLog.txt", FILE_WRITE); // 14
  if (dataFile) {
    dataFile.println(comp); // 3
    dataFile.close();       // 12
    Serial.println(comp);
  } else {
    Serial.println("error opening datalog.txt");
  }
  if (Serial.available()) {
    if (Serial.read() == 6) {
      Serial.flush();
      dataFile = SD.open("DataLog.txt");
      if (dataFile) {
        // read from the file until there's nothing else in it:
        while (dataFile.available()) {
          Serial.write(dataFile.read());
          // Serial.println(dataFile.read());
        }
        // close the file:
        dataFile.close();
        Serial.println("File Closed");
      } else {
        // if the file didn't open, print an error:
        Serial.println("error opening .txt");
      }
    }
  }
}

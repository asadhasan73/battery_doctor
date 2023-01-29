# battery_doctor
Software code from my bachelor's thesis: Battery Doctor

This code is an example of data logging to an SD card using an Adafruit ADS1115 16-Bit ADC and a Dallas DS18B20 temperature sensor.

It includes the following libraries:

Adafruit_ADS1015.h

SPI.h

SD.h
SoftwareSerial.h
Wire.h
stdio.h
OneWire.h
DallasTemperature.h

In the setup() function, it initializes the serial communication, the ADC, and the SD card. In the loop() function, it takes the readings from the ADC and the temperature sensor, and writes them as a single string (separated by semicolons) to a file named "DataLog.txt" on the SD card. The data is also printed on the serial monitor. If a 6 is received on the serial communication, it opens and prints the content of "DataLog.txt" to the serial monitor.

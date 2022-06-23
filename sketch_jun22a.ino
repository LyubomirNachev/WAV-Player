#include <SPI.h>
#include "SdFat.h"
#include "LiquidCrystal.h"
int SD_CS_PIN = 10;

SdFat sd;
void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("SD Card directory sorting...");
  if (!sd.begin(SD_CS_PIN)) {
    Serial.println("SD card error!");
    while (true);
  }
  sd.ls("/", LS_R);
}
void loop() {
  
}

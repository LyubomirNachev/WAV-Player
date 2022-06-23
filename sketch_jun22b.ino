#include<SPI.h>
#include "SdFat.h"
#define CS 10

SdFat sd;
SdFile file;
SdFile dirFile;

int numberOfFiles = 0;
char storage[100];
int x = 0;
void setup() 
{
  Serial.begin(9600);
  while (!Serial);
  if (!sd.begin(CS)) 
  {
    Serial.println("SD failed");
    while(true);
  }
  dirFile.open("/", O_READ);
  printDirectory(&dirFile);
  for(int i=0;i<=x;i++){
    Serial.println(storage[i]);
    }
}
void printDirectory (SdFile* CFile)
{
  while (file.openNext(CFile, O_READ)) 
  {
        Serial.println(file.printName());
        storage[x] = file.printName();
        x++;
        Serial.println();
        file.close();
  }
}

void loop(){}

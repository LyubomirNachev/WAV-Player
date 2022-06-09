#include "SPI.h"
#include "SD.h"
#include "TMRpcm.h"
#include "LiquidCrystal.h"
#define SCK 13
#define MISO 12
#define MOSI 11
#define CS 10
#define Speaker  9
#define Button  2 //active high button
TMRpcm audiotmr;
LiquidCrystal lcd(3, 2, A3, A2, A1, A0);
char song[] = "2.wav";
File root;
File myFile;

void setup() 
{
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);
  lcd.begin(16, 2);
  lcd.clear();
  Serial.begin(9600);
  audiotmr.speakerPin = Speaker;
  if(!SD.begin(CS))
  {
    Serial.println("SD failed");
    return;
  }
  root = SD.open("/");
  printDirectory(root, 0);
//  myFile = SD.open("storage.txt", FILE_WRITE);
//  if(myFile){
//    myFile.println(printDirectory(root, 0));
//    myFile.println("test proba ");
//    myFile.close();
//  }
  myFile = SD.open("storage.txt");
  if (myFile) {
    Serial.println("storage.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  play();
}

char* printDirectory(File dir, int numTabs) {
  char* array_wav = ".WAV";
  myFile = SD.open("storage.txt", FILE_WRITE);
  while (true) {

      File entry = dir.openNextFile();
      if (! entry) {
         // no more files
         break;
      }
      for (uint8_t i = 0; i < numTabs; i++) {
      }
      char* filename = entry.name();
      char* ext = &filename[strlen(filename)-4];
      if(!strcmp(ext, array_wav)){
        myFile.println(filename);
      }
      if (entry.isDirectory()) {
         myFile.println("/");
         printDirectory(entry, numTabs + 1);
      } else {
         // files have sizes, directories do not
         //Serial.println(entry.size(), DEC);
      }
      entry.close();
      myFile.close();
   }
}

void play()
{
  audiotmr.play(song);
  
  delay(100);
  return;
}


void loop() 
{
 int value = analogRead(A4);
 int Volume = analogRead(A5);
  if (value > 850 && value < 1000) {
    lcd.clear();
    lcd.print("Button1");
  } else if (value > 810 && value < 850) {
    lcd.scrollDisplayLeft();
  } else if (value > 740 && value < 810) {
    if (audiotmr.isPlaying() == 1){
      audiotmr.pause();
      lcd.setCursor(0, 1);
      lcd.print("Paused"); 
    }else{
      audiotmr.pause();
      lcd.setCursor(0, 1);
      lcd.print("neshto"); 
    }
    
  } else if (value > 600 && value < 740) {
    lcd.scrollDisplayRight();
  } else if (value > 450 && value < 600) {
    lcd.clear();
    lcd.print("Button5");
  } else if (value < 450) {
    lcd.clear();
    lcd.print("Button6");
  }
  if (Volume > 900 && Volume < 1050){
    audiotmr.setVolume(6);
  }else if (Volume > 750 && Volume < 900){
    audiotmr.setVolume(5);
  }else if (Volume > 650 && Volume < 750){
    audiotmr.setVolume(4);
  }else if (Volume > 550 && Volume < 650){
    audiotmr.setVolume(3);
  }else if (Volume > 450 && Volume < 550){
    audiotmr.setVolume(2);
  }else if (Volume > 350 && Volume < 450){
    audiotmr.setVolume(1);
  }else if (Volume > 250 && Volume < 350){
    audiotmr.setVolume(0);
  }else if (Volume > 0 && Volume < 250){
    audiotmr.setVolume(0); 
  }
  
  delay(100);
}

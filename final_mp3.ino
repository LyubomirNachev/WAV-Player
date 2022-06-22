#include "SPI.h"
#include "SD.h"
#include "TMRpcm.h"
#include "LiquidCrystal.h"
#define SCK 13
#define MISO 12
#define MOSI 11
#define CS 10
#define Speaker 9
TMRpcm audiotmr;
LiquidCrystal lcd(3, 2, A3, A2, A1, A0);
char song[] = "2.WAV";
File root;
int pause_m = 1;
char *storage_array[100];
int x=0;

byte Sound[8] = {
  0b00001,
  0b00011,
  0b00101,
  0b01001,
  0b01001,
  0b01011,
  0b11011,
  0b11000
};

void setup() {
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);
  lcd.createChar(5, Sound);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.write(byte(5));
  lcd.print(" WAV Player ");
  lcd.write(byte(5));
  Serial.begin(9600);
  audiotmr.speakerPin = Speaker;
  if(!SD.begin(CS))
  {
    Serial.println("SD failed");
    return;
  }
  root = SD.open("/");
  printDirectory(root, 0);
  printArray();
  play();
  audiotmr.pause();

}

void printArray(){
  int i = 0;
  while (i <= x) {
    //Serial.println(storage_array[i]);
    //Serial.println(' ');
    i++;
  }
}


char* printDirectory(File dir, int numTabs) {
  char* array_wav = ".WAV";
  while (true) {
      File entry = dir.openNextFile();
      if (! entry) {
         // no more files
         break;
      }
      for (uint32_t i = 0; i < numTabs; i++) {
      }
      char* filename = entry.name();
      char* extension = &filename[strlen(filename)-4];
      if(!strcmp(extension, array_wav)){ // we add ! because strcmp returns 0 on true
        storage_array[x]= filename;
        Serial.println(storage_array[x]);
        x++;
      }
      if (entry.isDirectory()) {
         storage_array[x] = "/";
         printDirectory(entry, numTabs + 1);
         x++;
      }
   }
}

void play()
{
  audiotmr.play(song);
  
  delay(100);
  return;
}


void loop() {
  int value = analogRead(A4);
  int Volume = analogRead(A5);
  
  //Buttons
  //Serial.println("Button:");
  //Serial.println(value);
  
  if (value > 850 && value < 1000) {
    if (pause_m == 0){
      audiotmr.pause();
      lcd.setCursor(0, 1);
      lcd.print("Paused"); 
      pause_m = 1;
    }else if(pause_m == 1){
      audiotmr.pause();
      lcd.setCursor(0, 1);
      lcd.print("      ");
      pause_m = 0;
    } 
  } else if (value > 810 && value < 850) {
    lcd.clear();
    lcd.print("Button2");
  } else if (value > 740 && value < 810) {
    lcd.clear();
    lcd.print("Button3");
  } else if (value > 600 && value < 740) {
    lcd.clear();
    lcd.print("Button4");
  } else if (value > 450 && value < 600) {
    lcd.clear();
    lcd.print("Button5");
  } else if (value < 450) {
    Serial.println(audiotmr.isPlaying());
    lcd.clear();
    lcd.print("Button6");
  }
  //Volume control
  //Serial.println("Volume:");
  //Serial.println(Volume);
   
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

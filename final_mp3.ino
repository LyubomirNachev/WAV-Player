#include <SPI.h>
#include <SdFat.h>
SdFat sd;
#include <pcmConfig.h>
#include <pcmRF.h>
#include <TMRpcm.h>
#include "LiquidCrystal.h"
#define SCK 13
#define MISO 12
#define MOSI 11
#define CS 10
#define Speaker 9
TMRpcm audiotmr;
LiquidCrystal lcd(3, 2, A3, A2, A1, A0);
char song[] = "2.WAV";
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
  while (!Serial);
  audiotmr.speakerPin = Speaker;
  if(!sd.begin(CS)){
    Serial.println("SD failed");
    while(true);
  }
  sd.ls("/", LS_R);
  play();
  audiotmr.pause();
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
  Serial.println(digitalRead(9));
  
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

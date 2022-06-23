#include <SPI.h>
#include <SdFat.h>
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
int pause_m = 1;
int x=0;
char* music[] = {"elsys.wav", "Little Dark Age.wav", "Meow Meow.wav", "North Memphis.wav", "Radiohead - Creep.wav", "Zyzz.wav", "Molchat Doma - Sudno.wav", "Jaba.wav", "Million theme.wav", "System Of A Down BYOB.wav", "kokosha glava homoseks.wav", "Straight to Hell.wav", "MBT Polov Jivot.wav", "Rammstein - Du Hast.wav", "Otlichen6-Nightcore.wav", "kokosha glava magazin.wav"};
SdFat sd;
int i;
//char song = music[x];

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
  for(i = 0; i < sizeof(music)/sizeof(music[0]);i++){
    Serial.println(music[i]);  
  }
  Serial.println(i);
  audiotmr.pause();
}
void loop() {
  int value = analogRead(A4);
  int Volume = analogRead(A5);
  
  //Buttons
  //Serial.println("Button:");
  //Serial.println(value);
  
  if (value > 850 && value < 1000) {
    //PAUSE
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
    //NEXT
    if(x==i){
      x = -1;
    };
    x++;
    lcd.clear();
    lcd.print(music[x]);
    audiotmr.play(music[x]);
  } else if (value > 740 && value < 810) {
    //LOOP
    lcd.clear();
    lcd.print("Button3");
  } else if (value > 600 && value < 740) {
    //PREV
    if(x==0){
      x = i;
    };
    x--;
    lcd.clear();
    lcd.print(music[x]);
    audiotmr.play(music[x]);
  } else if (value > 450 && value < 600) {
    //SHUFFLE
    x = rand() % i;
    lcd.clear();
    lcd.print(music[x]);
    audiotmr.play(music[x]);
  } else if (value < 450) {
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

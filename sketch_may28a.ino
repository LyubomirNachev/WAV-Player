#include "SD.h"
#include "TMRpcm.h"
#include "SPI.h"
#include "LiquidCrystal.h"
char song[] = "2.wav";
LiquidCrystal lcd(3, 2, A3, A2, A1, A0);
TMRpcm tmrpcm;

void setup(){
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
  tmrpcm.speakerPin = 9;
  Serial.begin(9600);
  if (!SD.begin(10)) {
    Serial.println("SD fail");
    return;
  }
  else{
    Serial.println("Raboti");  
  }

  tmrpcm.setVolume(5);
  tmrpcm.play(song);
}

void loop(){ 
  int value = analogRead(A4);
  if (value > 850 && value < 1000) {
    lcd.clear();
    lcd.print("Button1");
  } else if (value > 810 && value < 850) {
    lcd.scrollDisplayLeft();
  } else if (value > 740 && value < 810) {
    lcd.clear();
    lcd.print("Button3");
  } else if (value > 600 && value < 740) {
    lcd.scrollDisplayRight();
  } else if (value > 450 && value < 600) {
    lcd.clear();
    lcd.print("Button5");
  } else if (value < 450) {
    Serial.println(tmrpcm.isPlaying());
    lcd.clear();
    lcd.print("Button6");
  }
  delay(100);
}

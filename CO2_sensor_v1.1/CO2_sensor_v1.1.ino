#include <EEPROM.h>
#include "LCD_1602_RUS.h"
LCD_1602_RUS lcd(0x3F, 16, 2);
int sensorValue = 0;
long timer = 300000; //300000,  2000
int firstsetup = 0;
int limit = 500;
int buttonState;
void setup(){
  Serial.begin(9600);
  pinMode(6, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, INPUT_PULLUP);
  lcd.init();                      
  lcd.backlight();
  lcd.setCursor(0, 0);
  EEPROM.get(2, firstsetup);
  //digitalWrite(6, HIGH);
  if(firstsetup == 0){
    Serial.println("delay 5000");
    delay(1800000); //1800000,  5000
    EEPROM.put(2, 1);
  }
  else{
    Serial.println("delay 2000");
    delay(timer); 
  }  
  //digitalWrite(6, LOW);
}   
void loop() { 
  buttonState = digitalRead(12);
  if(buttonState == 0){
    limit = analogRead(A0);
    tone(11, 1000);
    EEPROM.put(1, limit);
    Serial.println("push");
    delay(200);
    noTone(11); 
    for (int i = 0 ; i < 10 ; i++) {
      EEPROM.write(i, 0);
    }
  }
  sensorValue = analogRead(A0); 
  lcd.setCursor(0, 0); 
  lcd.print(sensorValue);
  Serial.println(sensorValue); 
  EEPROM.put(1, limit);
  if(sensorValue < limit + 20){
    digitalWrite(6, LOW);
    noTone(11);
  }
  if(sensorValue > limit + 5 && sensorValue < limit + 10){
    if(round(millis() / 1000) % 2 == 0){
      digitalWrite(6, HIGH);
      Serial.println("alarm");
    }
    else{
      digitalWrite(6, LOW);
    }
  }
  if(sensorValue > limit + 10 && sensorValue < limit + 15){
    if(round(millis() / 500) % 2 == 0){
      digitalWrite(6, HIGH);
      tone(11, 1000);
      Serial.println("alarm");
    }
    else{
      digitalWrite(6, LOW);
      noTone(11); 
    }
  }
  if(sensorValue > limit + 15){
    if(round(millis() / 200) % 2 == 0){
      digitalWrite(6, HIGH);
      tone(11, 1000);
      Serial.println("alarm");
    }
    else{
      digitalWrite(6, LOW);
      noTone(11); 
    }
  }
}

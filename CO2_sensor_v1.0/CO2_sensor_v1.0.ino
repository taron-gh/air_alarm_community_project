unsigned long timer = 86400000;
int butstate = 0;

#include "LCD_1602_RUS.h"

LCD_1602_RUS lcd(0x3F, 16, 2);
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  lcd.init();                      // initialize the lcd
  // Print a message to the LCD.
  lcd.backlight();
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(4, INPUT_PULLUP);
  while(millis() < timer){
    
  }
}

// the loop routine runs over and over again forever:
void loop() {
  
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  if(sensorValue > 750){
    buzz();
  }
  // print out the value you read:
  lcd.setCursor(0,0);
  lcd.print(sensorValue);
  Serial.println(sensorValue);
  delay(1);        // delay in between reads for stability
  
}

void buzz(){
  digitalWrite(3, HIGH);
  while(butstate == 0){
    if(digitalRead(4) == LOW){
      butstate = 1;
    }
    for(int i = 0; i < 1000; i++){
      digitalWrite(2, LOW);
      delayMicroseconds(500);
      digitalWrite(2, HIGH);
      delayMicroseconds(500);
    } 
  }
  butstate = 0;
}

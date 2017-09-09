#include "Arduino.h"

void setup(){

  //Pin write
  digitalWrite(12, HIGH);

  //Setup pins
  pinMode(12, OUTPUT);
  pinMode(11, INPUT);

  Serial.begin(9600);
}

void loop(){

  int temp = digitalRead(11);
  Serial.print(temp);

  delay(50);
}
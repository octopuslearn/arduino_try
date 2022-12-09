#include <Arduino.h>

void setup() {
  pinMode(13,OUTPUT);
  pinMode(1,OUTPUT);
}

void loop() {
  digitalWrite(13,LOW);
  delay(10000);
  digitalWrite(13,HIGH);
  delay(1000);
  digitalWrite(1,LOW);
}
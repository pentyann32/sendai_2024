#include <avr/io.h>

int sleep_pin = 2;
int reset_pin = 3;
int rightmoter_clock = 9;
int leftmoter_clock = 10;
int right_sensor = A0;
int left_sensor = A1;
int right_direction = 11;
int left_direction= 12;

void setup() {
  TCCR2B = (TCCR2B & 0b00111111) | 0x01;
  TCCR2A = (TCCR2A & 0b00111111) | 0x01;
  pinMode(sleep_pin,OUTPUT);
  pinMode(reset_pin,OUTPUT);
  pinMode(right_direction,OUTPUT);
  pinMode(left_direction,OUTPUT);
  digitalWrite(reset_pin,HIGH);
  delay(100);
  digitalWrite(reset_pin,LOW);
  digitalWrite(sleep_pin,LOW);
  analogWrite(rightmoter_clock,127);
  analogWrite(leftmoter_clock,127);
}

void loop() {
  if(analogRead(right_sensor) < 150 && analogRead(left_sensor) >= 150){
    digitalWrite(right_direction,HIGH);
    digitalWrite(left_direction,LOW)
  else if(analogRead(right_sensor) >=150 && analogRead(left_sensor) < 150){
    digitalWrite(right_direction,LOW);
    digitalWrite(left_direction,HIGH);
  }else{
    digitalWrite(right_direction,LOW);
    digitalWrite(left_direction,LOW);
  }
}

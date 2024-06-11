#include <avr/io.h>
#include <Servo.h>
#include <Wire.h>

Servo kaitenservo;
Servo armservo;
int reset_pin = 30;
int right_clock = 9;
int left_clock = 10;
int right_sensor = A1;
int left_sensor = A0;
int right_direction = 8;
int left_direction = 12;
int kyuuinnmoter_1 = 52;
int kyuuinnmoter_2 = 53;

int sikiiti = 300;

void setup(){
  Serial.begin(9600);
  TCCR2B = (TCCR2B & 0b00111111) | 0x01;
  TCCR2A = (TCCR2A & 0b00111111) | 0x01;
  pinMode(right_direction,OUTPUT);
  pinMode(left_direction,OUTPUT);
  pinMode(kyuuinnmoter_1,OUTPUT);
  pinMode(kyuuinnmoter_2,OUTPUT);
  pinMode(reset_pin,OUTPUT);
  pinMode(left_clock,OUTPUT);
  pinMode(right_clock,OUTPUT);
  kaitenservo.attach(29);
  armservo.attach(31);
  armservo.write(100);
  kaitenservo.write(90);
  digitalWrite(reset_pin,HIGH);
  delay(100);
  digitalWrite(reset_pin,LOW);
  analogWrite(right_clock,127);
  analogWrite(left_clock,127);
  delay(500);
  if(analogRead(rightsensor)>sikiiti && analogRead(left_sensor)>sikiiti){
    digitalWrite(left_clock,LOW);
    digitalWrite(right_clock,LOW);
    delay(10);
    
  }
}

void linetrace(){
  analogWrite(right_clock,127);
  analogWrite(left_clock,127);
  if(analogRead(right_sensor) < sikiiti && analogRead(left_sensor) >= sikiiti){
    digitalWrite(right_direction,HIGH);
    digitalWrite(left_direction,LOW);
  }else if(analogRead(right_sensor) >=sikiiti && analogRead(left_sensor) < sikiiti){
    digitalWrite(right_direction,LOW);
    digitalWrite(left_direction,HIGH);
  }else{
    digitalWrite(right_direction,LOW);
    digitalWrite(left_direction,LOW);
  }
}

void kaitenn(){
  digitalWrite(left_clock,HIGH);
  digitlaWrite(right_clock,HIGH);
  delay(30);
  digitalWrite(left_clock,LOW);
  digitlaWrite(right_clock,LOW);
  delay(30);
}

void loop() {
}

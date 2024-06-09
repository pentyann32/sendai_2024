#include <avr/io.h>
#include <Servo.h>
#include <Wire.h>

Servo kaitenservo;
Servo armservo;
int sleep_pin = 2;
int reset_pin = 30;
int rightmoter_clock = 9;
int leftmoter_clock = 10;
int right_sensor = A1;
int left_sensor = A0;
int right_direction = 8;
int left_direction = 12;
int kyuuinnmoter_1 = 52;
int kyuuinnmoter_2 = 53;

void linetrace(){
  if(analogRead(right_sensor) < 150 && analogRead(left_sensor) >= 150){
    digitalWrite(right_direction,HIGH);
    digitalWrite(left_direction,LOW);
  }else if(analogRead(right_sensor) >=150 && analogRead(left_sensor) < 150){
    digitalWrite(right_direction,LOW);
    digitalWrite(left_direction,HIGH);
  }else{
    digitalWrite(right_direction,LOW);
    digitalWrite(left_direction,LOW);
  }
}

void setup(){
  Serial.begin(9600);
  kaitenservo.attach(29);
  armservo.attach(31);
  pinMode(kyuuinnmoter_1,OUTPUT);
  pinMode(kyuuinnmoter_2,OUTPUT);
  delay(100);
  armservo.write(90);
}

void loop() {
}

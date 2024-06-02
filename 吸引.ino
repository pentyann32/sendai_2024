#include <Servo.h>
int d = 30;
int sensor;
int p = 0;
Servo kaitenservo;
Servo armservo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  kaitenservo.attach(9);
  armservo.attach(11);
  pinMode(8,OUTPUT);
  pinMode(10,OUTPUT);
  delay(100);
  armservo.write(90);
  digitalWrite(8,LOW);
  digitalWrite(10,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  kaitenservo.write(d);
  delay(100);
  digitalWrite(8,LOW);
  digitalWrite(10,LOW);
  Serial.println(analogRead(1));
  if(analogRead(1) > 350 && analogRead(1)<420){
    kaitenservo.write(d+7);
    armservo.write(180);
    digitalWrite(8,HIGH);
    digitalWrite(10,LOW);
    delay(3000);
    armservo.write(165);
    delay(100);
    armservo.write(150);
    delay(100);
    armservo.write(135);
    delay(100);
    armservo.write(120);
    delay(100);
    armservo.write(105);
    delay(100);
    armservo.write(90);
    delay(1000);
  }else{
    d = d + 3;
  }
  if(d>150){
    d = 30;
  }
  p = 0;
  delay(100);
}

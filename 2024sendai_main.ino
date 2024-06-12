//ライブラリの設定
#include <avr/io.h>
#include <Servo.h>
#include <Wire.h>
//ピンの名前の設定
Servo kaitenservo;
Servo armservo;
int reset_pin = 30;
int right_clock = 9;
int left_clock = 10;
int right_direction = 8;
int left_direction = 12;
int kyuuinnmoter_1 = 52;
int kyuuinnmoter_2 = 53;

int marker_1 = 0;
int marker_2 = 0;　//マーカーを読んだ回数
int sikiiti = 300; //白と黒のしきい値

//関数ゾーン
void linetrace(){
  analogWrite(right_clock,127);
  analogWrite(left_clock,127);
  if(analogRead(A2) < sikiiti && analogRead(A1) >= sikiiti){
    digitalWrite(right_direction,HIGH);
    digitalWrite(left_direction,LOW);
  }else if(analogRead(A2) >=sikiiti && analogRead(A1) < sikiiti){
    digitalWrite(right_direction,LOW);
    digitalWrite(left_direction,HIGH);
  }else{
    digitalWrite(right_direction,LOW);
    digitalWrite(left_direction,LOW);
  }
}

void kaitenn(){
  digitalWrite(left_clock,HIGH);
  digitalWrite(right_clock,HIGH);
  delay(30);
  digitalWrite(left_clock,LOW);
  digitalWrite(right_clock,LOW);
  delay(30);
}

void LED_white(){  //RGBLEDを白色に点灯させる関数
  digitalWrite(3,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(7,HIGH);
}

//初期設定＆自由ボール（リセット後一回だけ実行）
void setup(){
  Serial.begin(9600);
  pinMode(right_direction,OUTPUT);
  pinMode(left_direction,OUTPUT);
  pinMode(kyuuinnmoter_1,OUTPUT);
  pinMode(kyuuinnmoter_2,OUTPUT);
  pinMode(reset_pin,OUTPUT);
  pinMode(left_clock,OUTPUT);
  pinMode(right_clock,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(7,OUTPUT);
  kaitenservo.attach(29);
  armservo.attach(31);
  armservo.write(100);
  kaitenservo.write(90);
  //ステッパーの初期設定
  TCCR2B = (TCCR2B & 0b00111111) | 0x01; //右モーターのPWM周期の設定
  TCCR2A = (TCCR2A & 0b00111111) | 0x01; //左モーターのPWM周期の設定
  digitalWrite(reset_pin,HIGH);
  delay(100);
  digitalWrite(reset_pin,LOW);
  digitalWrite(left_direction,LOW);
  digitalWrite(right_direction,LOW);
  while(marker_1 == 0){　//スタートラインを読む前の話
    analogWrite(right_clock,127); //右モーターにPWMを流す
    analogWrite(left_clock,127);  //左モーターにPWMを流す
    if(analogRead(A0)<sikiiti && analogRead(A3)<sikiiti){　//ラインを読んだとき
      digitalWrite(left_clock,LOW);  //左モーターを止める
      digitalWrite(right_clock,LOW); //右モーターを止める
      delay(500); //0.5秒停止
      //0.5秒前進（スタートラインを二回判定しないようにする）
      analogWrite(right_clock,127);
      analogWrite(left_clock,127); 
      delay(500);
      marker_1 = 1;　//ラインを読んだ回数を1回にする
    }
  }while(marker_1 == 1){　//スタートラインだけを読んだとき
    if(analogRead(A0)<sikiiti && analogRead(A3)<sikiiti){　//ラインを読んだとき
      //任意の角度右回りする（ラインの誤検出を防ぐ）
      digitalWrite(left_direction,LOW);
      digitalWrite(right_direction,HIGH);
      delay(300);
      while(analogWrite(A0)>sikiiti){  //90°回るまで
        //右回りし続ける
      }
      //ラインに対して90°になったとき,後ろに0.5秒進む
      digitalWrite(left_direction,HIGH);
      delay(500);
      while(analogRead(A0)>sikiiti){　//元の位置に戻るまで
        //前進する
        digitalWrite(left_direction,LOW);
        digitalWrite(right_direction,LOW);
      }
      //任意の角度左回りする（ラインの誤検出を防ぐ）
      digitalWrite(left_direction,HIGH);
      digitalWrite(right_direction,LOW);
      delay(300);
      while(analogRead(A0)>sikiiti || analogRead(A3)){  //左又は右が白（ライン上に復帰するまで）
        //左回りし続ける
      }
      marker_1 = 2;　//ライン上に復帰したら次の処理に行く
    }else{　//スタートラインと一本目の線の間にいる時
      //両方のモーターを正転
      digitalWrite(right_direction,LOW);
      digitalWrite(left_direction,LOW);
      analogWrite(right_clock,127);
      analogWrite(left_clock,127);  
    }  
  }while(marker_2 <5){　//自由ボールを落とした後探索エリアにつくまで
    if(analogRead(A0)<sikiiti && analogRead(A3)<sikiiti){
      digitalWrite(left_clock,LOW);  //左モーターを止める
      digitalWrite(right_clock,LOW); //右モーターを止める
      delay(500); //0.5秒停止
      //0.5秒前進（スタートラインを二回判定しないようにする）
      analogWrite(right_clock,127);
      analogWrite(left_clock,127); 
      delay(500);
      marker_2 = marker_2 + 1;　//ラインを読んだ回数を増やす
    }else{
      linetrace();
    } 
  }
  //ラインを読んだ回数が5回になったら（探索エリアに入ったら）上のwhileを満たさないからloopの方に進む
  LED_white();
}

void loop() {
}

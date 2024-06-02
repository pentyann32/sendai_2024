/*
 * RGBC Timing Register(0x01)   Control Register (0x0F)
 * 0xFF cycle 1     2.4ms       0x00  1×gain
 * 0xF6 cycle 10    24ms        0x01  4×gain
 * 0xD5 cycle 42    101ms       0x10  16×gain
 * 0xC0 cycle 64    156ms       0x11  60×gain
 * 0x00 cycle 256   700ms
 */

#include <Wire.h>
const int ADDRESS=0x29;//TCS34725アドレス
uint8_t id;//ID Register値
uint8_t ATIME=0x00;//積分時間×256cycle(700ms)
uint8_t AGAIN=0x10;//ゲイン×60
uint8_t ENABLE=0b00000011;//割り込み✕,待機✕,ADC〇,電源ON〇
uint8_t CRGB[8];//RGBC ADC値各2byteずつ格納
uint8_t i=0;
uint16_t Clear, Red, Green, Blue;

void setup() {
  Serial.begin(115200);
  Wire.begin();//I2Cマスター初期化

  Wire.beginTransmission(ADDRESS);
  Wire.write(0b10000000|0x12);//Register指定コマンド+ID Register
  Wire.endTransmission(false);//コネクション維持
  Wire.requestFrom(ADDRESS, 1);//スレーブアドレスに1バイト読み取り要求
  while(Wire.available()){
  id = Wire.read();
  }
  Serial.print("TCS34725固有ID:");
  Serial.println(id,HEX);//TCS34725固有ID

    //積分時間
  Wire.beginTransmission(ADDRESS);
  Wire.write(0b10000000|0x01);//Register指定コマンド+RGBC Timing Register
  Wire.write(ATIME);//×256cycle指定
  Wire.endTransmission();
  //ゲイン
  Wire.beginTransmission(ADDRESS);
  Wire.write(0b10000000|0x0F);//Register指定コマンド+Control Register
  Wire.write(AGAIN);//4×gain指定
  Wire.endTransmission();
  //ADC,電源ON
  Wire.beginTransmission(ADDRESS);
  Wire.write(0b10000000|0x00);//Register指定コマンド+Enable Register
  Wire.write(ENABLE);//ADC開始,電源オン
  Wire.endTransmission();
  //ウォームアップ2.4ms
  delay(3);
}

void loop() {
  //ADC読み取り
  Wire.beginTransmission(ADDRESS);
  Wire.write(0b10100000|0x14);//Register指定コマンド(インクリメント)+ADC Channel Register
  Wire.endTransmission(false);//コネクション維持
  Wire.requestFrom(ADDRESS, 8);//スレーブアドレスに1バイト読み取り要求
  //C(2byte)⇒R(2byte)⇒G(2byte)⇒B(2byte)
  i=0;
  while(Wire.available()){
    CRGB[i]=Wire.read();
    i++;
    //Serial.println("読み取り中");
  }

  //色統合
  Clear = CRGB[0]|CRGB[1]<<8;
  Red   = CRGB[2]|CRGB[3]<<8;
  Green = CRGB[4]|CRGB[5]<<8;
  Blue  = CRGB[6]|CRGB[7]<<8;

   Serial.print("透明：");Serial.println(Clear);
   Serial.print("赤：");Serial.println(Red);
   Serial.print("緑：");Serial.println(Green);
   Serial.print("青：");Serial.println(Blue);
   Serial.println("");
  
   if(Clear < 5000){
    if(Red - Green < 500 && Red > Blue){
      Serial.println("黄");
    }else if(Red - Green > 500 && Red > Blue){
      Serial.println("赤");
    }else{
      Serial.println("青");
    }
   }else{
      Serial.println("ボールはありません");
   } 

   delay(800);
}
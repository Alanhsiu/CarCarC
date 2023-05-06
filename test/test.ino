/* TODO:
pinMode setup
set direction when getting wifi result
TFT text direction
*/

#include <SPI.h>
#include <MFRC522.h>
#include <DistanceSensor.h>
#include <SparkFun_TB6612.h>

#define AI12 22
#define AI11 24
#define STBY1 26
#define BI11 28
#define BI12 30
#define PWMA1 2
#define PWMB1 3

// #define AI22 32
// #define AI21 34
// #define STBY2 36
// #define BI21 38
// #define BI22 40
// #define PWMA2 4
// #define PWMB2 5

#define AI32 42
#define AI31 44
#define STBY3 46
// #define BI31 48
// #define BI32 50
#define PWMA3 6
// #define PWMB3 7

// #define RFID_RST 9
// #define RFID_SS 10

#define TRIG1 37
#define ECHO1 35
// #define TRIG2 49
// #define ECHO2 47

// #define TFT 33
// #define AMBIENT 31

// #define ESP0 39
// #define ESP1 41
// #define ESP2 43
// #define ESP3 45

// int target=0;// result from wifi
int direction=1;
// int seats=0;//need to reset when getting new command from wifi
// bool open=false;
// MFRC522 mfrc522(RFID_SS, RFID_RST);
DistanceSensor ultrasonic1(TRIG1, ECHO1);
// DistanceSensor ultrasonic2(TRIG2, ECHO2);
Motor car1 = Motor(AI11, AI12, PWMA1, 1, STBY1);
Motor car2 = Motor(BI11, BI12, PWMB1, 1, STBY1);
// Motor car3 = Motor(AI21, AI22, PWMA2, 1, STBY2);
// Motor car4 = Motor(BI21, BI22, PWMB2, 1, STBY2);
Motor trashcan = Motor(AI31, AI32, PWMA3, 1, STBY3);

void setup() {

  Serial.begin(9600); 
  // SPI.begin();
  // mfrc522.PCD_Init();
  // pinMode(ESP0,INPUT);
  // pinMode(ESP1,INPUT);
  // pinMode(ESP2,INPUT);
  // pinMode(ESP3,INPUT);
}

void loop() {
  // if(target>0)
  // {
    // carDrive(direction);
    // if(ultrasonic1.getCM()<20)
    // {
    //   carDrive(2);
    //   while(ultrasonic1.getCM()<20)
    //   {
    //     // digitalWrite(TFT,HIGH);
       
    //   }
    //   // digitalWrite(TFT,LOW);
    //   carDrive(direction);
    // }
    //  Serial.println(ultrasonic1.getCM());
    // if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    //     mfrc522.PICC_HaltA();
    //     seats+=1;
    // }
    // if(seats==target)
    // {
    //   carDrive(2);
    //   int ambientStatus=digitalRead(AMBIENT);
    //   if(ambientStatus==HIGH&&!open)
    //   {
      trashcan.drive(-255, 1000);
      trashcan.drive(255,1000);      
      // if(Serial.available())
      // {
      //   int speed=Serial.read()=='c'?255:-255;
        
      // }
    //     open=1;
    //   }
    //   else if(ambientStatus==LOW&&open)
    //   {
    //     trashcan.drive(-255,1000);
    //     open=0;
    //   }
    // }
    // }
}

void carDrive(int mode)
{
  switch(mode){
    case 0://back
      back(car1,car2,150);
      // back(car3,car4,150);
      break;
    case 1://forward
      forward(car1,car2,150);
      // forward(car3,car4,150);
      break;    
    case 2://stop
      brake(car1,car2);
      // brake(car3,car4);
      break;  
  }
}
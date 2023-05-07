/* TODO:
pinMode setup
set direction when getting wifi result
TFT text direction
*/

#include <SPI.h>
#include <MFRC522.h>
#include <DistanceSensor.h>
#include <SparkFun_TB6612.h>
#include <ArduinoQueue.h>

#define AI12 22
#define AI11 24
#define STBY1 26
#define BI11 28
#define BI12 30
#define PWMA1 2
#define PWMB1 3

#define AI22 32
#define AI21 34
#define STBY2 36
#define BI21 38
#define BI22 40
#define PWMA2 4
#define PWMB2 5

#define AI32 42
#define AI31 44
#define STBY3 46
#define BI31 48
#define BI32 50
#define PWMA3 6
#define PWMB3 7

#define RFID_RST 8
#define RFID_SS 53

#define TRIG1 37
#define ECHO1 35
#define TRIG2 49
#define ECHO2 47

#define TFT 33
#define AMBIENT 31

#define ESP1 39
#define ESP2 41
#define ESP3 43
#define ESP4 45

#define LED 13

int direction=1;
int seats=0;//need to reset when getting new command from wifi
bool open=0;
MFRC522 mfrc522(RFID_SS, RFID_RST);
DistanceSensor ultrasonic1(TRIG1, ECHO1);
DistanceSensor ultrasonic2(TRIG2, ECHO2);
Motor car1 = Motor(AI11, AI12, PWMA1, 1, STBY1);
Motor car2 = Motor(BI11, BI12, PWMB1, 1, STBY1);
Motor car3 = Motor(AI21, AI22, PWMA2, 1, STBY2);
Motor car4 = Motor(BI21, BI22, PWMB2, 1, STBY2);
Motor trashcan = Motor(AI31, AI32, PWMA3, 1, STBY3);
int currentPosition=1;
int tmp=0;
ArduinoQueue<int>target(20);

void setup() {

  Serial.begin(9600); 
  SPI.begin();
  mfrc522.PCD_Init();
  pinMode(TFT,OUTPUT);
  pinMode(AMBIENT,INPUT);
  pinMode(ESP1,INPUT);
  pinMode(ESP2,INPUT);
  pinMode(ESP3,INPUT);
  pinMode(ESP4,INPUT);
  brake(car1,car2);
  brake(car3,car4);
  trashcan.brake();
  pinMode(LED,OUTPUT);
}

void loop() {
  // int ambientStatus=digitalRead(AMBIENT);
  // Serial.println(ambientStatus);
  // if(ambientStatus==HIGH&&!open)
  // {
    trashcan.drive(-255,6000);
  //   open=1;
  // }
  // else if(ambientStatus==LOW&&open)
  // {
  //   trashcan.drive(-255,6000);
  //   open=0;
  // }
  // else
  // {
  //   trashcan.brake();
  // }
}

void carDrive(int mode)
{
  switch(mode){
    case 0://stop
      brake(car1,car2);
      brake(car3,car4);
      break;     
    case 1://forward
      forward(car1,car2,150);
      forward(car3,car4,150);
      break;
    case 2://back
      back(car1,car2,150);
      back(car3,car4,150);
      break;
  }
}
void readTarget()
{
  if(digitalRead(ESP1)==HIGH){
    if(tmp!=1){
      Serial.println("ESP1");
      target.enqueue(1);
      tmp=1;
    }
  }
  
  else if(digitalRead(ESP2)==HIGH){
    if(tmp!=2){
      Serial.println("ESP2");
      target.enqueue(2);
      tmp=2;
    }
  }
  else if(digitalRead(ESP3)==HIGH){
    if(tmp!=3){
      Serial.println("ESP3");
      target.enqueue(3);
      tmp=3;
    }
  }
  else if(digitalRead(ESP4)==HIGH){
    if(tmp!=4){
      Serial.println("ESP4");
      target.enqueue(4);
      tmp=4;
    }
  }
}

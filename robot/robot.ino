#include "TRSensors.h"
#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
#define PIN 7
#define NUM_SENSORS 5
#define rxPin 4
#define txPin 3
TRSensors trs =   TRSensors();
unsigned int sensorValues[NUM_SENSORS];
unsigned int last_proportional = 0;
long integral = 0;

#define PWMA   6           //Left Motor Speed pin (ENA)
#define AIN2   A0          //Motor-L forward (IN2).
#define AIN1   A1          //Motor-L backward (IN1)
#define PWMB   5           //Right Motor Speed pin (ENB)
#define BIN1   A2          //Motor-R forward (IN3)
#define BIN2   A3          //Motor-R backward (IN4)

Adafruit_NeoPixel RGB = Adafruit_NeoPixel(4, PIN, NEO_GRB + NEO_KHZ800);
SoftwareSerial mySerial(rxPin, txPin);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("TRSensor example!!");
  RGB.begin();
  RGB.show();
  pinMode(PWMA,OUTPUT);                     
  pinMode(AIN2,OUTPUT);      
  pinMode(AIN1,OUTPUT);
  pinMode(PWMB,OUTPUT);       
  pinMode(AIN1,OUTPUT);     
  pinMode(AIN2,OUTPUT);   
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  mySerial.begin(9600);

}


void loop() {
  String receivedChar="";
  if (mySerial.available()) {
    receivedChar = mySerial.readString();

    if (receivedChar == "AVANCER") {
      forward();
      delay(1000);
      stop();
    } else if (receivedChar == "RECULER") {
      backward();
      delay(1000);
      stop();
    } else if (receivedChar == "A_DROITE") {
      right();
      delay(1000);
      stop();
    } else if (receivedChar == "A_GAUCHE") {
      left();
      delay(1000);
      stop();
    } else if (receivedChar == "STOP"){
      stop();
      delay(500);
    }
    else{
      mySerial.print("NOK");
    }
  }
}

  void forward(){
  RGB.setPixelColor(0, 0x00FF00);
  RGB.setPixelColor(1, 0x00FF00);
  RGB.setPixelColor(2, 0x00FF00);
  RGB.setPixelColor(3, 0x00FF00);
  analogWrite(PWMA,100);
  analogWrite(PWMB,100);
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,HIGH);
  digitalWrite(BIN1,LOW); 
  digitalWrite(BIN2,HIGH);
  RGB.show();  
  }

  void backward(){
  RGB.setPixelColor(0, 0xFF0000);
  RGB.setPixelColor(1, 0xFF0000);
  RGB.setPixelColor(2, 0xFF0000);
  RGB.setPixelColor(3, 0xFF0000);
  analogWrite(PWMA,100);
  analogWrite(PWMB,100);
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,HIGH); 
  digitalWrite(BIN2,LOW);  
  RGB.show(); 
  }

void right()
{
  RGB.setPixelColor(0, 0x0000FF);
  RGB.setPixelColor(1, 0x0000FF);
  RGB.setPixelColor(2, 0x0000FF);
  RGB.setPixelColor(3, 0x0000FF);
  analogWrite(PWMA,80);
  analogWrite(PWMB,80);
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,HIGH);
  digitalWrite(BIN1,HIGH); 
  digitalWrite(BIN2,LOW);  
  RGB.show(); 
}

void left()
{
  RGB.setPixelColor(0, 0xFBFF00);
  RGB.setPixelColor(1, 0xFBFF00);
  RGB.setPixelColor(2, 0xFBFF00);
  RGB.setPixelColor(3, 0xFBFF00);
  analogWrite(PWMA,80);
  analogWrite(PWMB,80);
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,LOW); 
  digitalWrite(BIN2,HIGH);  
  RGB.show(); 
}

void stop(){
  RGB.setPixelColor(0, 0xFBFF00);
  RGB.setPixelColor(1, 0xFBFF00);
  RGB.setPixelColor(2, 0xFBFF00);
  RGB.setPixelColor(3, 0xFBFF00);
  analogWrite(PWMA,0);
  analogWrite(PWMB,0);
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,LOW); 
  digitalWrite(BIN2,LOW);  
  RGB.show(); 

}



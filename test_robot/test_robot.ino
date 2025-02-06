#include "TRSensors.h"
#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>

#define PIN 7
#define NUM_SENSORS 5
#define rxPin 3
#define txPin 2
#define PWMA 6
#define AIN2 A0
#define AIN1 A1
#define PWMB 5
#define BIN1 A2
#define BIN2 A3

class Robot {
private:
    TRSensors trs;
    unsigned int sensorValues[NUM_SENSORS];
    unsigned int last_proportional = 0;
    long integral = 0;
    Adafruit_NeoPixel RGB;
    SoftwareSerial mySerial;

public:
    Robot() : RGB(4, PIN, NEO_GRB + NEO_KHZ800), mySerial(rxPin, txPin) {}

    void setup() {
        Serial.begin(9600);
        Serial.println("TRSensor example!!");
        RGB.begin();
        RGB.show();
        pinMode(PWMA, OUTPUT);
        pinMode(AIN2, OUTPUT);
        pinMode(AIN1, OUTPUT);
        pinMode(PWMB, OUTPUT);
        pinMode(BIN1, OUTPUT);
        pinMode(BIN2, OUTPUT);
        pinMode(rxPin, INPUT);
        pinMode(txPin, OUTPUT);
        mySerial.begin(9600);
    }

    void loop() {
        String receivedChar = "";
        if (mySerial.available()) {
            receivedChar = mySerial.readString();
            if (receivedChar == "avancer") {
                forward();
            } else if (receivedChar == "reculer") {
                backward();
            } else if (receivedChar == "a_droite") {
                right();
            } else if (receivedChar == "a_gauche") {
                left();
            } else if (receivedChar == "stop") {
                stop();
            } else {
                mySerial.print("NOK");
            }
        }
    }

    void forward() {
        setColor(0x00FF00);
        moveMotors(100, 100, LOW, HIGH, LOW, HIGH);
    }

    void backward() {
        setColor(0xFF0000);
        moveMotors(100, 100, HIGH, LOW, HIGH, LOW);
    }

    void right() {
        setColor(0x0000FF);
        moveMotors(80, 80, LOW, HIGH, HIGH, LOW);
    }

    void left() {
        setColor(0xFBFF00);
        moveMotors(80, 80, HIGH, LOW, LOW, HIGH);
    }

    void stop() {
        setColor(0xFBFF00);
        moveMotors(0, 0, LOW, LOW, LOW, LOW);
    }

private:
    void setColor(uint32_t color) {
        for (int i = 0; i < 4; i++) {
            RGB.setPixelColor(i, color);
        }
        RGB.show();
    }

    void moveMotors(int speedA, int speedB, int dirA1, int dirA2, int dirB1, int dirB2) {
        analogWrite(PWMA, speedA);
        analogWrite(PWMB, speedB);
        digitalWrite(AIN1, dirA1);
        digitalWrite(AIN2, dirA2);
        digitalWrite(BIN1, dirB1);
        digitalWrite(BIN2, dirB2);
    }
};

Robot robot;

void setup() {
    robot.setup();
}

void loop() {
    robot.loop();
}

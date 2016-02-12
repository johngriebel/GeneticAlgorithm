#include <Arduino.h>
#include <vector>
#include <fstream>
#include "Controller.h"
using namespace std;
Params* p;
Sensor sensor;
Controller* controller = NULL;
int RIGHTDIR = 4;   
int RIGHT = 5;
int LEFT = 6;
int LEFTDIR = 7;  
int RIGHTBUMPER = 0;
int FRONTBUMPER = 1;
int LEFTBUMPER = 2;
int REARBUMPER = 3;

void setup() {
    Serial.begin(9600);
    delay(3000);
    controller = new Controller();
    
    pinMode(RIGHTBUMPER, INPUT);
    digitalWrite(RIGHTBUMPER, HIGH);
    
    pinMode(FRONTBUMPER, INPUT);
    digitalWrite(FRONTBUMPER, HIGH);
    
    pinMode(LEFTBUMPER, INPUT);
    digitalWrite(LEFTBUMPER, HIGH);
    
    pinMode(REARBUMPER, INPUT);
    digitalWrite(REARBUMPER, HIGH);
    
    pinMode(RIGHTDIR, OUTPUT);   
    pinMode(RIGHT, OUTPUT);
    pinMode(LEFT, OUTPUT);
    pinMode(LEFTDIR, OUTPUT);
}

void loop() {
    //HIGH=Backwards
    digitalWrite(RIGHTDIR,LOW);   
    digitalWrite(LEFTDIR, LOW);       
    analogWrite(RIGHT, 0);   //PWM Speed Control
    analogWrite(LEFT, 175);   //PWM Speed Control
    delay(250);
    
    //while the controller will update correctly, delay 10 seconds between generations
    // while(controller->runGeneration(sensor)){
    //   delay(10000);
    // }
    delay(1000);
}

void readSensors(){
    Serial.print("Left IR Sensor: ");
    Serial.println(sensor.readLeft());
    
    Serial.print("Left Middle IR Sensor: ");
    Serial.println(sensor.readLeftMiddle());
    
    Serial.print("Front IR Sensor: ");
    Serial.println(sensor.readFront());
    
    Serial.print("Right Middle IR Sensor: ");
    Serial.println(sensor.readRightMiddle());
    
    Serial.print("Right IR Sensor: ");
    Serial.println(sensor.readRight());
    
    Serial.print("Rear IR Sensor: ");
    Serial.println(sensor.readRear());
}

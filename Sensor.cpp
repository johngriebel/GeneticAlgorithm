#include "Sensor.h"
//Hello world
Sensor::Sensor(){
    pinMode(rightSensor, INPUT);
    pinMode(rightMiddleSensor, INPUT);
    pinMode(frontSensor, INPUT);
    pinMode(leftMiddleSensor, INPUT);
    pinMode(leftSensor, INPUT);
    pinMode(rearSensor, INPUT);
}
// TODO: What are all of these constants? Why did you do that? Ugh.
double Sensor::changeToCm (uint16_t value) {
    if (value < 21){ 
        value = 21;
    }
    return 4800 / (value - 20.0);
}
//Different function because we ran out of the same type of sensor...
double Sensor::changeToCmLeft (uint16_t value) {
    if (value < 16){ 
        value = 16;
    }
    return 2076.0 / (value - 11.0);
}

double Sensor::readLeft(){
    uint16_t sensorValueLeft = analogRead(leftSensor);
    return changeToCmLeft(sensorValueLeft);
}

double Sensor::readLeftMiddle(){
    uint16_t sensorValueLeftMiddle = analogRead(leftMiddleSensor);
    return changeToCm(sensorValueLeftMiddle);
}


double Sensor::readFront(){
    uint16_t sensorValueFront = analogRead(frontSensor);
    return changeToCm(sensorValueFront);
}


double Sensor::readRightMiddle(){
        uint16_t sensorValueRightMiddle = analogRead(rightMiddleSensor);
        return changeToCm(sensorValueRightMiddle);
}

double Sensor::readRight(){
        uint16_t sensorValueRight = analogRead(rightSensor);
        return changeToCm(sensorValueRight);
}

double Sensor::readRear(){
        uint16_t sensorValueRear = analogRead(rearSensor);
        return changeToCm(sensorValueRear);
}

vector<double> Sensor::readAll(){
  vector<double> vals;
  vals.push_back(readLeft());
  vals.push_back(readLeftMiddle());
  vals.push_back(readFront());
  vals.push_back(readRightMiddle());
  vals.push_back(readRight());
  vals.push_back(readRear());
  return vals;
}

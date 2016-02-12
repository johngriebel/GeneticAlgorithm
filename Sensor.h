#ifndef Sensor_h
#define Sensor_h
#include <Arduino.h>
#include <stdint.h>
#include <vector>
using namespace std;
class Sensor{
    public:
        Sensor();
        double readLeft();
        double readLeftMiddle();
        double readFront();
        double readRightMiddle();
        double readRight();
        double readRear();
        vector<double> readAll();
    private:
        double changeToCm(uint16_t value);
        double changeToCmLeft(uint16_t value);
        static const uint8_t rightSensor = A0;
        static const uint8_t rightMiddleSensor = A1;
        static const uint8_t frontSensor = A2;
        static const uint8_t leftMiddleSensor = A3;
        static const uint8_t leftSensor = A4;
        static const uint8_t rearSensor = A5;
};

#endif

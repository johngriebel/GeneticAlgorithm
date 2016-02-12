/*
 * Controller.h
 *
 *  Created on: Feb 28, 2015
 *      Author: jgriebel
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <Arduino.h>
#include "Sensor.h"
#include "GeneticAlg.h"
#include "NeuralNet.h"
#include "Member.h"
#include "Params.h"

using namespace std;

class Controller {
    private:
        vector<Genome> thePopulation;
        vector<Member> members;
        GeneticAlg* ga;
      	int numMembers;
      	int curGeneration;
      	int numWeightsInNN;
        static const int rightDirection=4;
        static const int rightSpeed=5;
        static const int leftDirection=7;
        static const int leftSpeed=6;
        static const int rightBumper = 0;
        static const int frontBumper = 1;
        static const int leftBumper = 2;
        static const int rearBumper = 3;
        double getMaxTimeForGen();
        int readBumpers();
    public:
        Controller();
      	boolean runGeneration(Sensor s);
        boolean checkForCollision(double left, double right);
        double sendLeftMotor(double val);
        double sendRightMotor(double val);
        void writeToFile();
        void initFromFile();
        void printStuff();
        void writeToLogFiles();
};

#endif /* CONTROLLER_H_ */

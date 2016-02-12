/*
 * Params.h
 *
 *  Created on: Feb 28, 2015
 *      Author: jgriebel
 */
#ifndef PARAMS_H_
#define PARAMS_H_
#include <fstream>
#include <Arduino.h>

class Params {
    public:
        Params(){
            Serial.println("In Params constructor");
            if(!loadInParams()){
                Serial.println("Error, cannot find init file");
            }
        }
      	//Neural Network settings
      	static int numInputs;
      	static int numHidden;
      	static int neuronsPerHiddenLayer;
      	static int numOutputs;
      	//Tweak sigmoid function
      	static double activationResponse;
      	static double bias;
      	//GA params and state
        static int popSize;
      	static double crossoverRate;
      	static double mutationRate;
        static int curGeneration;
        static double totalFitness;
        static double bestFitness;
        static double worstFitness;
        static double averageFitness;
        static int fittestGenome;
      	//Max amount GA may mutate a weight by
      	static double maxPerturbation;
      	static int numElite;
      	static int numCopiesElite;
        boolean loadInParams();
        
};

#endif /* PARAMS_H_ */

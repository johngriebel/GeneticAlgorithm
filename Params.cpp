/*
 * Params.cpp
 *
 *  Created on: Feb 28, 2015
 *      Author: jgriebel
 */

#include "Params.h"
using namespace std;
int Params::numInputs=0;
int Params::numHidden=0;
int Params::neuronsPerHiddenLayer=0;
int Params::numOutputs=0;
double Params::activationResponse=0;
double Params::bias=0;
double Params::crossoverRate=0;
double Params::mutationRate=0;
double Params::maxPerturbation=0;
int Params::numElite=0;
int Params::numCopiesElite=0;
int Params::popSize = 0;
int Params::curGeneration=0;
double Params::totalFitness=0.0;
double Params::bestFitness=0.0;
double Params::worstFitness=0.0;
double Params::averageFitness=0.0;
int Params::fittestGenome=0.0;

boolean Params::loadInParams(){
    ifstream file;
    file.open("/standard_params.txt");
    if(!file.is_open()){
        Serial.println("Failed to open file");
        return false;
    }
    //Used as somewhat of a dummy string, we don't need the name of the parameter...
    //So we just read it into this variable and do nothing with it
    char paramDesc[40];
    file >> paramDesc;
    file >> Params::numInputs;
    file >> paramDesc;
    file >> numHidden;
    file >> paramDesc;
    file >> neuronsPerHiddenLayer;
    file >> paramDesc;
    file >> numOutputs;
    file >> paramDesc;
    file >> activationResponse;
    file >> paramDesc;
    file >> bias;
    file >> paramDesc;
    file >> crossoverRate;
    file >> paramDesc;
    file >> mutationRate;
    file >> paramDesc;
    file >> maxPerturbation;
    file >> paramDesc;
    file >> numElite;
    file >> paramDesc;
    file >> numCopiesElite;
    file >> paramDesc;
    file >> popSize;
    
    file.close();
    Serial.print("numInputs: ");
    Serial.println(numInputs);
    ifstream dynFile;
    dynFile.open("/dynamic_params.txt");
    if(!dynFile.is_open())
        return false;
    dynFile >> paramDesc;
    dynFile >> curGeneration;
    dynFile >> paramDesc;
    dynFile >> totalFitness;
    dynFile >> paramDesc;
    dynFile >> bestFitness;
    dynFile >> paramDesc;
    dynFile >> worstFitness;
    dynFile >> paramDesc;
    dynFile >> averageFitness;
    dynFile >> paramDesc;
    dynFile >> fittestGenome;
}


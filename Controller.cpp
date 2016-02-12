/*
 * Controller.cpp
 *
 *  Created on: Feb 28, 2015
 *      Author: jgriebel
 */

#include "Controller.h"
#include <Arduino.h>

Controller::Controller(){
  Serial.println("Entered constructor");
  Params* p = new Params();
  Serial.print("Params::numInputs: ");
  Serial.println(Params::numInputs);
  numMembers = Params::popSize;
  curGeneration = Params::curGeneration;
  
  if(curGeneration==0){
      Serial.println("In if");
      Serial.println(numMembers);
      for(int i=0; i<numMembers;i++){
          Serial.println("Creating members");
          members.push_back(Member());
      }
	    numWeightsInNN = members[0].getNumberOfWeights();
	    ga = new GeneticAlg(numMembers, Params::mutationRate, Params::crossoverRate, numWeightsInNN);

	    thePopulation = ga->getChromos();
	    for(int i=0;i<numMembers;i++){
          Serial.println("Putting weights");
	        members[i].putWeights(thePopulation[i].vecWeights);
	    }
  }
  else{
      initFromFile(); 
  }
}

//runs one generation
boolean Controller::update(Sensor s){
    for(int i=0; i<numMembers;i++){
        unsigned long initTime = millis();
        double fit = 0.0;
        while(fit < getMaxTimeForGen()){
            vector<double> speeds;
            speeds = members[i].update(s.readAll());
            if(speeds.size() != 2){
                return false;
            }
        fit += sendLeftMotor(speeds[0]);
        fit += sendRightMotor(speeds[1]);
        delay(250);
        if(checkForCollision(speeds[0],speeds[1]))
            break;
            //How many seconds the robot has gone at the assigned speed
            fit = ((millis()-initTime)*fit)/1000;
            members[i].setFitness(fit);
            thePopulation[i].fitness = fit;
        }
    }
    sendLeftMotor(0);
    sendRightMotor(0);
    //A generation has been completed...
    curGeneration++;
    thePopulation = ga->epoch(thePopulation);
    for(int i=0;i<numMembers;i++){
        members[i].putWeights(thePopulation[i].vecWeights);
        members[i].resetMem();
    }
    writeToFile();
    return true;
}
//verify direction settings...
double Controller::sendLeftMotor(double val){
  double retVal = 0.0;
  if(val < 0) {
      digitalWrite(leftDirection, HIGH);
      analogWrite(leftSpeed, (-255 * val));
      retVal += 0.1* - 255 * val;
  }
  else{
      digitalWrite(leftDirection, LOW);
      analogWrite(leftSpeed, (255 * val));
      retVal += 255*val;
  }
  return retVal;
}

double Controller::sendRightMotor(double val){
    int retVal=0.0;
    if(val <0){
        digitalWrite(rightDirection, HIGH);
        analogWrite(rightSpeed, (-255 * val));
        retVal += 0.1* -255*val;
    }
    else{
        digitalWrite(rightDirection, LOW);
        analogWrite(rightSpeed, (255 * val));
        retVal += 255*val;
    }
    return retVal;
}

void Controller::writeToFile(){
    ofstream file;
    file.open("/genomes.txt");
    file << ga->getGeneration()<<"\n";
    for(int i=0;i<thePopulation.size();i++){
        for(int j=0;j<thePopulation[i].vecWeights.size()-1;j++){
          file << thePopulation[i].vecWeights[j] << " ";
        }
        file << thePopulation[i].vecWeights[thePopulation[i].vecWeights.size()-1] << "\n";
    }
    
    file.close();
    
    ofstream dParamsFile;
    dParamsFile.open("/dynamic_params.txt");
    // TODO: Make a method that will do this
    dParamsFile << "curGeneration " << ga->getGeneration() << "\n";
    dParamsFile << "totalFitness " << ga->getTotalFitness() << "\n";
    dParamsFile << "bestFitness " << ga->getBestFitness()<<"\n";
    dParamsFile << "worstFitness " << ga->getWorstFitness()<<"\n";
    dParamsFile << "averageFitness" << ga->getAverageFitness()<<"\n";
    dParamsFile << "fittestGenome " << ga->getFittestGenome()<<"\n";
    dParamsFile.close();
}
// TODO: Why is this blank? I'm reasonably sure I've seen this method called somewhere
void Controller::writeToLogFiles(){
  
}
// TODO: Consider using a db? Might not be great for Arduino but investigate
void Controller::initFromFile(){
    Serial.println("Init from file...");
    ifstream file;
    file.open("/genomes.txt");
    
    for(int i=0; i<numMembers;i++){
  		  members.push_back(Member());
    }
    
    if(file.is_open()){
        for(int i=0;i<Params::popSize;i++){
            double weights[48];
            for(int j=0; j<48;j++){
                file >> weights[j];
            }
            vector<double> weightsVec;
            for(int k=0; k<48;k++){
                weightsVec.push_back(weights[k]);
            }
            unsigned long fit;
            file >> fit;
            members.push_back(Member(weightsVec, fit));
        }
        numWeightsInNN = members[0].getNumberOfWeights();
        ga = new GeneticAlg(Params:: popSize, Params::mutationRate, Params::crossoverRate, numWeightsInNN, Params::totalFitness, Params::bestFitness, Params::worstFitness, Params::averageFitness, Params::curGeneration, Params::fittestGenome, members);
        file.close();
    }
}

double Controller::getMaxTimeForGen(){
    return ((0.1385*(curGeneration*curGeneration)) - (1.4461*curGeneration) + 18.959) * 1000;
}

boolean Controller::checkForCollision(double left, double right){
    int check = readBumpers();
    if(check == -1){
        return false;
     }
    else{
        if(check == 2 || check ==9){
            sendLeftMotor(-left);
            sendRightMotor(-right);
        }
        else{
            sendLeftMotor(right);
            sendRightMotor(left);
        }
        delay(1000);
        return true; 
    }
}

int Controller::readBumpers(){
 if(digitalRead(leftBumper) == 0)
    return leftBumper;
 else if(digitalRead(frontBumper == 0))
    return frontBumper;
 else if(digitalRead(rightBumper == 0))
    return rightBumper;
 else if(digitalRead(rearBumper == 0))
    return rearBumper;
 else
    return -1;
}

void Controller::printStuff(){
    Serial.print("numMembers");
    Serial.println(numMembers);
}

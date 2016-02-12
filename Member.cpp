/*
 * Member.cpp
 *
 *  Created on: Feb 28, 2015
 *      Author: jgriebel
 */

#include "Member.h"

Member::Member(): fitness(0){}

Member::Member(vector<double> weights, unsigned long fit){
    brain.putWeights(weights);
    fitness = fit;
}

void Member::resetMem(){
	  fitness=0;
}

vector<double> Member::update(vector<double> sensors){
    return brain.update(sensors);
}

void Member::setFitness(unsigned long curTime){
    fitness += curTime - fitness; 
}

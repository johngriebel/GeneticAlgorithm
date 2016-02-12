/*
 * Member.h
 *
 *  Created on: Feb 28, 2015
 *      Author: jgriebel
 */

#ifndef MEMBER_H_
#define MEMBER_H_

#include <vector>
#include <math.h>

#include "NeuralNet.h"
#include "Params.h"

using namespace std;

class Member{
	private:
	    NeuralNet brain;
	    unsigned long fitness;
	public:
		Member();
      	Member(vector<double> weights, unsigned long fitness);
  		vector<double> update(vector<double> sensors);
  		void resetMem();
      	void setFitness(unsigned long curTime);
		unsigned long getFitness()const{return fitness;}
      	vector<double> getWeights(){return brain.getWeights();};
	  	void putWeights(vector<double> &w){brain.putWeights(w);}
		int getNumberOfWeights()const {return brain.getNumberOfWeights();}
};

#endif

/*
 * GeneticAlg.h
 *
 *  Created on: Feb 28, 2015
 *      Author: jgriebel
 */

#ifndef GENETICALG_H_
#define GENETICALG_H_

#include <vector>
#include <iostream>
#include <fstream>
#include "utils.h"
#include "Params.h"
#include "Member.h"

using namespace std;

struct Genome{
  	vector<double> vecWeights;
  	double fitness;
  	Genome():fitness(0){}
  	Genome(vector<double> w, double f):vecWeights(w), fitness(f){}
};

class GeneticAlg {
private:
  	vector<Genome> vecPop;
  	int popSize;
    int currentGeneration;
  	int chromoLength;
  	double totalFitness;
  	double bestFitness;
  	double averageFitness;
  	double worstFitness;
  	int fittestGenome;
  	double mutationRate;
  	double crossoverRate;
  	int curGeneration;
  	void crossover(const vector<double> &mother, const vector<double> &father, vector<double> &off1, vector<double> &off2);
  	void mutate(vector<double> &chromo);
  	Genome getChromoRoulette();
  	void grabNBest(int nBest, const int numCopis, vector<Genome> &vectorPop);
  	//calculate best, worst, average, and total
  	void doCalculations();
  	void resetAlg();

public:
  	GeneticAlg();
  	GeneticAlg(int pSize, double mutRate, double crossRate, int numWeights);
    GeneticAlg(int pSize, double mutRate, double crossRate, int numWeights, double totalFit, double bestFit, double worstFit, double averageFit, int curGen, int fittestGene, vector<Member> members);
    void sortPop(vector<Genome> &vecPop);
    void setGeneration(int gen);
    void copyFromMembers(vector<Member> members);
  	vector<Genome> epoch(vector<Genome> &old_pop);
  	//getters
  	vector<Genome> getChromos()const{return vecPop;};
    double getTotalFitness()const{return totalFitness;};
  	double getBestFitness()const{return bestFitness;};
    double getWorstFitness()const{return worstFitness;};
  	double getAverageFitness()const{return averageFitness;};
    int getGeneration()const{return curGeneration;};
    int getFittestGenome()const{return fittestGenome;};
};

#endif /* GENETICALG_H_ */


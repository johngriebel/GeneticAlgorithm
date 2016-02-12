/*
   GeneticAlg.cpp

    Created on: Feb 28, 2015
        Author: jgriebel
*/

#include "GeneticAlg.h"
GeneticAlg::GeneticAlg() {
  // TODO Auto-generated constructor stub
}

GeneticAlg::GeneticAlg(int pSize, double mutRate, double crossRate, int numWeights):
    popSize(pSize), mutationRate(mutRate), crossoverRate(crossRate), chromoLength(numWeights),
    totalFitness(0), curGeneration(0), fittestGenome(0), bestFitness(0), worstFitness(99999999),
    averageFitness(0){ 
    Serial.println("In GA Constructor");
    //initiliaze with random weights
    for (int i = 0; i < popSize; i++) {
        vecPop.push_back(Genome());
        for (int j = 0; j < chromoLength; j++) {
          vecPop[i].vecWeights.push_back(randomClamped());
        }
    }
}

// TODO: Can this maybe use a point to an array of args or something? Similar to Python's **kwargs
GeneticAlg::GeneticAlg(int pSize, double mutRate, double crossRate, int numWeights, double totalFit, double bestFit, double worstFit, double averageFit, int curGen, int fittestGene, vector<Member> members):
  popSize(pSize), mutationRate(mutRate), crossoverRate(crossRate), chromoLength(numWeights), totalFitness(totalFit), bestFitness(bestFit), worstFitness(worstFit), averageFitness(averageFit),
  currentGeneration(curGen), fittestGenome(fittestGene){
    
    for (int i = 0; i < popSize; i++) {
        vecPop.push_back(Genome(members[i].getWeights(), members[i].getFitness()));
    }
}

//Mutate a chromosome by changing its weights by no more that that specified in p.maxPerturbation
void GeneticAlg::mutate(vector<double> &chromo) {
    for (int i = 0; i < chromo.size(); i++) {
        if (randFloat() < mutationRate)
          chromo[i] = (randomClamped() * Params::maxPerturbation);
    }
}

Genome GeneticAlg::getChromoRoulette() {
    double slice = (double)(randFloat() * totalFitness);
    Genome chosen;
    double fitnessSoFar = 0;
    for (int i = 0; i < popSize; i++) {
        fitnessSoFar += vecPop[i].fitness;
        if (fitnessSoFar >= slice) {
            chosen = vecPop[i];
            break;
        }
    }
    return chosen;
}

void GeneticAlg::crossover(const vector<double> &mother, const vector<double> & father, vector<double> &child1, vector<double> &child2) {
    //If parents are the same or dont cross threshold, just return parents as children
    if ((randFloat() > crossoverRate) || (mother == father)) {
        child1 = mother;
        child2 = father;
        return;
    }
    int crossPoint = randInt(0, chromoLength - 1);
    //Create offspring
    for (int i = 0; i < crossPoint; i++) {
      child1.push_back(mother[i]);
      child2.push_back(father[i]);
    }
    for (int i = crossPoint; i < mother.size(); i++) {
        child1.push_back(father[i]);
        child2.push_back(mother[i]);
    }
    // TODO: Is this even necessary/does it do anything?
    return;
}

//Run the algorithm through one generation
//Returns a new population of chromosomes
//Need to add the idea of a time limit somehow

vector<Genome> GeneticAlg::epoch(vector<Genome> &oldPop) {
    vecPop = oldPop;
    resetAlg();
    sortPop(vecPop);
    currentGeneration++;
    doCalculations();
    vector<Genome> vecNewPop;
    //Add in copies of the fittest genomes. Must make sure to add an even number
    if (!(Params::numCopiesElite * Params::numElite % 2)) {
        grabNBest(Params::numElite, Params::numCopiesElite, vecNewPop);
    }
    //Now enter the GA loop
    //Repeat until the new population is filled
    while (vecNewPop.size() < popSize) {
        //grab two chromosomes
        Genome mother = getChromoRoulette();
        Genome father = getChromoRoulette();
        vector<double> child1, child2;
        //Create offspring via crossover
        crossover(mother.vecWeights, father.vecWeights, child1, child2);
        //Mutation...
        mutate(child1);
        mutate(child2);
        //Add new vectors to population..
        vecNewPop.push_back(Genome(child1, 0));
        vecNewPop.push_back(Genome(child2, 0));
    }
    vecPop = vecNewPop;
    return vecPop;
}

//Insert numCopies of the nBest most fit genomes into a population vector
void GeneticAlg::grabNBest(int nBest, const int numCopies, vector<Genome> &pop) {
    while (nBest--) {
        for (int i = 0; i < numCopies; i++) {
            pop.push_back(vecPop[(popSize - 1) - nBest]);
        }
    }
}

//Caclulate the fittest and weakest genomes as well as the average and total fitness scores

void GeneticAlg::doCalculations() {
    totalFitness = 0;
    double max = 0;
    double min = 9999999;
  
    for (int i = 0; i < popSize; i++) {
        if (vecPop[i].fitness > max) {
            max = vecPop[i].fitness;
            fittestGenome = i;
            bestFitness = max;
        }
        if (vecPop[i].fitness < min) {
            min = vecPop[i].fitness;
            worstFitness = min;
        }
      totalFitness += vecPop[i].fitness;
    }
    // TODO: This does integer division (I think.) Is that okay?
    averageFitness = totalFitness / popSize;
}
//TODO: We don't need a this.attr or self or w/e? Apparently not
void GeneticAlg::resetAlg() {
    totalFitness = 0;
    bestFitness = 0;
    worstFitness = 9999999;
    averageFitness = 0;
}

//TODO: Fix this
//inefficient but quick and dirty selection sort
//stl algorithm wouldnt import correctly
void GeneticAlg::sortPop(vector<Genome>& vecPop) {
    for (int i = 0; i < popSize - 1; i++) {
        for (int j = i + 1; j < popSize; j++) {
            if (vecPop[j].fitness < vecPop[i].fitness) {
                //swap
                Genome tmp = vecPop[i];
                vecPop[i] = vecPop[j];
                vecPop[j] = tmp;
            }
        }
    }
}

void GeneticAlg::copyFromMembers(vector<Member> members) {
    vector<Genome> newPop;
    for (int i = 0; i < popSize; i++) {
        newPop.push_back(Genome(members[i].getWeights(), members[i].getFitness()));
    }
    vecPop = newPop;
}

void GeneticAlg::setGeneration(int gen) {
    curGeneration = gen;
}

/*
 * NeuralNet.h

 *
 *  Created on: Feb 28, 2015
 *      Author: jgriebel
 */

#ifndef NEURALNET_H_
#define NEURALNET_H_
#include <vector>
#include <fstream>
#include <math.h>

#include "utils.h"
#include "Params.h"

using namespace std;

struct Neuron{
  	//number of inputs to the neuron
  	int numInputs;
  
  	//the weights for each input
  	vector<double> vecWeight;
  
  	Neuron(int numInputs);
};

struct NeuronLayer{
  	int numNeurons;
  	vector<Neuron> vecNeurons;
  	NeuronLayer(int numNeurons, int numInputsPerNeuron);
};
class NeuralNet {
    private:
      	int numInputs;
      	int numOutputs;
      	int numHiddenLayers;
      	int neuronsPerHiddenLayer;
      	//storage for each layer of neurons including the output layer
      	vector<NeuronLayer> vecLayers;
    public:
      	NeuralNet();
      	void createNet();
      	vector<double> getWeights()const;
      	int getNumberOfWeights()const;
      	//Set weights to a new vector
      	void putWeights(vector<double> &weights);
      	//Calculate output from a set of inputs
      	vector<double> update(vector<double> &inputs);
      	//sigmoid response curve
      	inline double sigmoid(double activation);
};

#endif /* NEURALNET_H_ */

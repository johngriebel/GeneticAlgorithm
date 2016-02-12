/*
 * NeuralNet.cpp
 *
 *  Created on: Feb 28, 2015
 *      Author: jgriebel
 */

#include "NeuralNet.h"
Neuron::Neuron(int newNumInputs): numInputs(newNumInputs+1){
  	//Need an additional weight for the bias
  	for (int i=0; i<newNumInputs+1;i++){
    		//Set up weights with a random initial value
    		vecWeight.push_back(randomClamped());
  	}
}

NeuronLayer::NeuronLayer(int newNumNeurons, int inPerNeuron) : numNeurons(newNumNeurons){
  	for (int i=0;i<newNumNeurons;i++){
  		  vecNeurons.push_back(Neuron(inPerNeuron));
  	}
}

NeuralNet::NeuralNet() {
  	numInputs = Params::numInputs;
  	numOutputs = Params::numOutputs;
  	numHiddenLayers = Params::numHidden;
  	neuronsPerHiddenLayer = Params::neuronsPerHiddenLayer;
  	createNet();
}

// all weights are initially set to random values -1<w<1
void NeuralNet::createNet(){
  	if(numHiddenLayers > 0){
    		vecLayers.push_back(NeuronLayer(neuronsPerHiddenLayer, numInputs));
    
    		for(int i=0;i<numHiddenLayers-1;i++){
    			vecLayers.push_back(NeuronLayer(neuronsPerHiddenLayer, neuronsPerHiddenLayer));
    		}
    		vecLayers.push_back(NeuronLayer(numOutputs,neuronsPerHiddenLayer));
  	}
  	else{
  		  vecLayers.push_back(NeuronLayer(numOutputs, numInputs));
  	}
}

vector<double> NeuralNet::getWeights() const{
  	vector<double> retWeights;
  
  	for(int i=0;i<numHiddenLayers;i++){
    		for(int j=0;j<vecLayers[i].numNeurons;j++){
      			for(int k=0;k<vecLayers[i].vecNeurons[j].numInputs;k++){
      				retWeights.push_back(vecLayers[i].vecNeurons[j].vecWeight[k]);
      			}
    		}
  	}
  	return retWeights;
}

void NeuralNet::putWeights(vector<double> &weights){
    int cWeight=0;
  
  	for(int i=0;i<numHiddenLayers+1;i++){
  	    for(int j=0;j<vecLayers[i].numNeurons;j++){
  			    for(int k=0;k<vecLayers[i].vecNeurons[j].numInputs;k++){
  				    vecLayers[i].vecNeurons[j].vecWeight[k] = weights[cWeight++];
  			    }
  		  }
  	}
  	return;
}

int NeuralNet::getNumberOfWeights()const{
  	int count = 0;
  	for(int i=0;i<numHiddenLayers+1;i++){
  			for(int j=0;j<vecLayers[i].numNeurons;j++){
  				  for(int k=0;k<vecLayers[i].vecNeurons[j].numInputs;k++){
  					    count++;
  				  }
  			}
  	}
  	return count;
}

vector<double> NeuralNet::update(vector<double> &inputs){
  	//stores the outputs from each layer
  	vector<double> outputs;
  	int cWeight = 0;
  
  	//incorrect # of inputs
  	if(inputs.size() != numInputs){
  		  return outputs;
  	}
  
  	//For each hidden layer
  	for(int i=0; i<numHiddenLayers+1;i++){
  		  if(i>0){
  			    inputs=outputs;
  		  }
  		  outputs.clear();
  		  cWeight=0;
  
    		//For each neuron calculate the sum and put in in the sigmoid function
    		for(int j=0;j<vecLayers[i].numNeurons;j++){
      			double netinput = 0;
      			int numInputs = vecLayers[i].vecNeurons[j].numInputs;
    			//for each weight
      			for(int k=0; k<numInputs-1;k++){
      				  netinput += vecLayers[i].vecNeurons[j].vecWeight[k] * inputs[cWeight++];
      			}
      			netinput += vecLayers[i].vecNeurons[j].vecWeight[numInputs-1] * Params::bias;
      			outputs.push_back(sigmoid(netinput));
      			cWeight=0;
  		}
  	}
  	return outputs;
}

//sigmoid function.
//What do here?
double NeuralNet::sigmoid(double netinput){
    //Use hyperbolic tangent because -1<tanh(x)<1
    //multiply return value by 255 to get both a direction and speed
    return tanh(netinput);
}

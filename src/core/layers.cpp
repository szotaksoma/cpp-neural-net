#include <stdlib.h>
#include "core/layers.h"
#include "core/activations.h"
#include "util/console.h"
#include "util/errors.h"

using namespace std;
using namespace NeuralNet;

// Layer

void Layer::bind(Layer* previous, Layer* next) {
	this->previous = previous;
	this->next = next;
	this->bound = true;
}

void Layer::initialize() {
	if(!bound) {
		Errors::layer_initialize_error("Unbound layer.");
	}
	values = (double*) calloc(size, sizeof(double));
	if(type == LayerType::INPUT) {
		biases = nullptr;
		weights = nullptr;
		return;
	}
	// Allocate biases
	biases = (double*) calloc(size, sizeof(double));
	// Allocate weights
	weights = (double**) calloc(size, sizeof(double*));
	for(unsigned int i = 0; i < size; i++) {
		weights[i] = (double*) calloc(previous->size, sizeof(double));
	}
}

// Get layer name
string Layer::name() {
	return this->_name;
}

// Set layer name
void Layer::rename(string name) {
	this->_name = name;
}

// Get layer description
string Layer::describe() {
	return this->_name + "\t[" + to_string(this->size) + "]" + "\t" + this->activation->name();
}

Layer::~Layer() {
	delete activation;
	if(values) {
		free((void*)values);
	}
	if(biases) {
		free((void*)biases);
	}
	if(weights) {
		for(unsigned int i = 0; i < size; i++) {
			free((void*)weights[i]);
		}
		free((void*)weights);
	}
}

// Input layer

InputLayer::InputLayer(unsigned int size, string name) {
	type = LayerType::INPUT;
	this->_name = name;
	this->activation = new Activations::Linear();
	this->size = size;
	this->weights = nullptr;
	this->biases = nullptr;
	trainable = false;
}

// Hidden layer

HiddenLayer::HiddenLayer(unsigned int size, Activations::ActivationType activation, string name) {
	type = LayerType::HIDDEN;
	this->_name = name;
	this->size = size;
	this->activation = Activations::default_activation(activation);
	this->weights = nullptr;
	this->biases = nullptr;
	trainable = true;
}

HiddenLayer::HiddenLayer(unsigned int size, Activations::Activation* activation, string name) {
	type = LayerType::HIDDEN;
	this->_name = name;
	this->size = size;
	this->activation = activation;
	this->weights = nullptr;
	this->biases = nullptr;
	trainable = true;
}

// Output layer

OutputLayer::OutputLayer(unsigned int size, string name) {
	type = LayerType::OUTPUT;
	this->_name = name;
	this->activation = new Activations::Linear();
	this->size = size;
	this->weights = nullptr;
	this->biases = nullptr;
	trainable = true;
}
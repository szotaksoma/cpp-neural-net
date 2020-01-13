#include <stdlib.h>
#include "core/layers.h"
#include "core/activations.h"
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
	// Allocate biases
	biases = (double*) calloc(size, sizeof(double));
	// Allocate weights
	weights = (double**) calloc(size, sizeof(double*));
	for(unsigned int i = 0; i < size; i++) {
		weights[i] = (double*) calloc(previous->size, sizeof(double));
	}
}

Layer::~Layer() {
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

InputLayer::InputLayer(unsigned int size) {
	type = LayerType::INPUT;
	this->size = size;
	trainable = false;
}

// Override Layer::initialize
void InputLayer::initialize() {
	if(!bound) {
		// TODO: raise exception
		// Cannot initialize unbound layer
	}
	biases = nullptr;
	weights = nullptr;
}

// Hidden layer

HiddenLayer::HiddenLayer(unsigned int size, Activations::ActivationType activation) {
	type = LayerType::HIDDEN;
	this->size = size;
	this->activation = Activations::default_activation(activation);
	trainable = true;
}

// Output layer

OutputLayer::OutputLayer(unsigned int size) {
	type = LayerType::OUTPUT;
	this->size = size;
	trainable = true;
}
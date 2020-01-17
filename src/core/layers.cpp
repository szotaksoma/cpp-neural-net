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
const char* Layer::get_name() {
	return this->name;
}

// Set layer name
void Layer::set_name(const char* name) {
	this->name = name;
}

// Get layer description
string Layer::describe() {
	return string(this->name) + "\t[" + to_string(this->size) + "]" + "\t" + this->activation->name;
}

Layer::~Layer() {
	delete activation;
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

InputLayer::InputLayer(unsigned int size, const char* name) {
	type = LayerType::INPUT;
	this->name = name;
	this->activation = new Activations::Linear();
	this->size = size;
	trainable = false;
}

// Hidden layer

HiddenLayer::HiddenLayer(unsigned int size, Activations::ActivationType activation, const char* name) {
	type = LayerType::HIDDEN;
	this->name = name;
	this->size = size;
	this->activation = Activations::default_activation(activation);
	trainable = true;
}

// Output layer

OutputLayer::OutputLayer(unsigned int size, const char* name) {
	type = LayerType::OUTPUT;
	this->name = name;
	this->activation = new Activations::Linear();
	this->size = size;
	trainable = true;
}
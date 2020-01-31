#include <stdlib.h>
#include <math.h>
#include <random>
#include "NeuralNet.h"

using namespace std;
using namespace NeuralNet;

void Layer::bind(Layer* previous, Layer* next) {
	this->previous = previous;
	this->next = next;
	this->bound = true;
}

void Layer::initialize() {
	if(!bound) {
		Errors::Layer::initialize_error("Unbound layer");
	}

	// Allocate values
	values = (double*) calloc(size, sizeof(double));

	if(type == LayerType::INPUT) {
		biases = nullptr;
		weights = nullptr;
		return;
	}

	// Allocate biases
	biases = (double*) calloc(size, sizeof(double));

	// Allocate weights
	weights = (double**) malloc(size * sizeof(double*));
	for(unsigned i = 0; i < size; i++) {
		weights[i] = (double*) malloc(previous->size * sizeof(double));
	}

	WeightInitializers::kaiming(this);

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

InputLayer::InputLayer(unsigned int size, string name) {
	type = LayerType::INPUT;
	this->_name = name;
	this->activation = new Activations::Linear();
	this->size = size;
	this->weights = nullptr;
	this->biases = nullptr;
	trainable = false;
}

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

OutputLayer::OutputLayer(unsigned int size, string name) {
	type = LayerType::OUTPUT;
	this->_name = name;
	this->activation = new Activations::Linear();
	this->size = size;
	this->weights = nullptr;
	this->biases = nullptr;
	trainable = true;
}

void WeightInitializers::kaiming(Layer* l) {
	static random_device rd{};
	static mt19937 gen{rd()};
	static normal_distribution<> dist{0.0, 1.0};
	const double factor = sqrt(2.0 / (double) l->previous->size);
	l->weights = (double**) malloc(l->size * sizeof(double*));
	for(unsigned i = 0; i < l->size; i++) {
		l->weights[i] = (double*) malloc(l->previous->size * sizeof(double));
		for(unsigned j = 0; j < l->previous->size; j++) {
			l->weights[i][j] = dist(gen) * factor;
		}
	}
}

void WeightInitializers::xavier(Layer* l) {
	static random_device rd{};
	static mt19937 gen{rd()};
	const double limit = sqrt(6.0 / (double) (l->size + l->previous->size));
	static uniform_real_distribution<> dist{-limit, limit};
	l->weights = (double**) malloc(l->size * sizeof(double*));
	for(unsigned i = 0; i < l->size; i++) {
		l->weights[i] = (double*) malloc(l->previous->size * sizeof(double));
		for(unsigned j = 0; j < l->previous->size; j++) {
			l->weights[i][j] = dist(gen);
		}
	}
}
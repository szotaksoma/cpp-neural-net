#include <stdlib.h>
#include <math.h>
#include <random>
#include "core/layers.h"
#include "core/activations.h"
#include "util/console.h"
#include "util/errors.h"

using namespace std;
using namespace NeuralNet;

// Initialize weights ["Kaiming"] (m -> layer size, n -> previous layer size)
void kaiming_weight_init(double** &w, unsigned int m, unsigned int n);

// Initialize weights ["Xavier"] (m -> layer size, n -> previous layer size)
void xavier_weight_init(double** &w, unsigned int m, unsigned int n);

void kaiming_weight_init(double** &w, unsigned int m, unsigned int n) {
	static random_device rd{};
	static mt19937 gen{rd()}; // TODO: decide which one of 'mt19937' and 'mt19937_64' to use as 'gen'
	static normal_distribution<> dist{0.0, 1.0};
	const double factor = sqrt(2.0 / (double) n);
	w = (double**) malloc(m * sizeof(double*));
	for(unsigned int i = 0; i < m; i++) {
		w[i] = (double*) malloc(n * sizeof(double));
		for(unsigned int j = 0; j < n; j++) {
			w[i][j] = dist(gen) * factor;
		}
	}
}

void xavier_weight_init(double** &w, unsigned int m, unsigned int n) {
	static random_device rd{};
	static mt19937 gen{rd()}; // TODO: decide which one of 'mt19937' and 'mt19937_64' to use as 'gen'
	static uniform_real_distribution<> dist{-1.0, 1.0};
	const double factor = sqrt(6.0 / (double) (m + n));
	w = (double**) malloc(m * sizeof(double*));
	for(unsigned int i = 0; i < m; i++) {
		w[i] = (double*) malloc(n * sizeof(double));
		for(unsigned int j = 0; j < n; j++) {
			w[i][j] = dist(gen) * factor;
		}
	}
}

void Layer::bind(Layer* previous, Layer* next) {
	this->previous = previous;
	this->next = next;
	this->bound = true;
}

void Layer::initialize() {
	if(!bound) {
		Errors::layer_initialize_error("Unbound layer");
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

	// Allocate and initialize weights
	kaiming_weight_init(weights, size, previous->size);
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
#include <math.h>
#include "NeuralNet.h"

using namespace std;
using namespace NeuralNet::Activations;

string Activation::name() {
	return this->_name;
}

// Linear

Linear::Linear() {
	this->type = ActivationType::LINEAR;
	this->_name = "Linear";
	this->m = default_m;
}

Linear::Linear(double slope) {
	this->type = ActivationType::LINEAR;
	this->m = slope;
}

double Linear::function(double x) {
	return m * x;
}

double Linear::derivative(double x) {
	return m;
}

// Rectified Linear Unit (ReLU)

ReLU::ReLU() {
	this->type = ActivationType::RELU;
	this->_name = "ReLU";
}

double ReLU::function(double x) {
	return x > 0.0 ? x : 0.0;
}

double ReLU::derivative(double x) {
	return x > 0.0 ? 1.0 : 0.0;
}

// Sigmoid

Sigmoid::Sigmoid() {
	this->type = ActivationType::SIGMOID;
	this->_name = "Sigmoid";
}

double Sigmoid::function(double x) {
	return 1.0 / (1.0 + exp(-x));
}

double Sigmoid::derivative(double x) {
	const double fx = function(x);
	return fx * (1.0 - fx);
}

// Hyperbolic tangent

TanH::TanH() {
	this->type = ActivationType::TANH;
	this->_name = "TanH";
}

double TanH::function(double x) {
	return tanh(x);
}

double TanH::derivative(double x) {
	return 1.0 - pow(tanh(x), 2.0);
}

// Helper functions

Activation* NeuralNet::Activations::default_activation(ActivationType type) {
	switch(type) {
		case LINEAR:
			return new Linear();
		case RELU:
			return new ReLU();
		case TANH:
			return new TanH();
		case SIGMOID:
			return new Sigmoid();
		default:
			return new Linear();
	}
}
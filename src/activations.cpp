#include "activations.h"

using namespace NeuralNet::Activations;

// Linear

Linear::Linear() {
	this->m = default_m;
}

Linear::Linear(double slope) {
	this->m = slope;
}

double Linear::function(double x) {
	return m * x;
}

double Linear::derivative(double x) {
	return m;
}

// Rectified Linear Unit (ReLU)

double ReLU::function(double x) {
	return x > 0.0 ? x : 0.0;
}

double ReLU::derivative(double x) {
	return x > 0.0 ? 1.0 : 0.0;
}

// Sigmoid

double Sigmoid::function(double x) {
	return 1.0 / (1.0 + exp(-x));
}

double Sigmoid::derivative(double x) {
	const double fx = function(x);
	return fx * (1.0 - fx);
}

// Hyperbolic tangent

double TanH::function(double x) {
	return tanh(x);
}

double TanH::derivative(double x) {
	return 1.0 - pow(tanh(x), 2.0);
}
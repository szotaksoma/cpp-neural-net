#include <stdlib.h>
#include "layers.h"
#include "activations.h"

using namespace std;
using namespace NeuralNet;

// Input layer

InputLayer::InputLayer(unsigned int size) {
	this->size = size;
	type = LayerType::Input;
	trainable = false;
	biases = nullptr;
	values = nullptr;
}

// Hidden layer

HiddenLayer::HiddenLayer(unsigned int size, Activations::ActivationType activation) {
	this->size = size;
	type = LayerType::Hidden;
	trainable = true;
	this->activation = Activations::default_activation(activation);
}
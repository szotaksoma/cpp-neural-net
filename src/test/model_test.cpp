#include "core/activations.h"
#include "core/model.h"

using namespace std;
using namespace NeuralNet;
using namespace NeuralNet::Activations;

int main(int argc, char* argv[]) {

	// Create model
	Model model;

	// Add input layer
	model.add_layer(new InputLayer(5));

	// Add 3 hidden layers with default sigmoid activations
	model.add_layer(new HiddenLayer(16, ActivationType::SIGMOID));
	model.add_layer(new HiddenLayer(32, ActivationType::SIGMOID));
	model.add_layer(new HiddenLayer(16, ActivationType::SIGMOID));
	
	// Add output layer
	model.add_layer(new OutputLayer(2));

	// Compile model
	model.compile();

	// Dispose model
	model.dispose();

	return 0;
}
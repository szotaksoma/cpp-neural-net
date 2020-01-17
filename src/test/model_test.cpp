#include "core/activations.h"
#include "core/model.h"
#include "util/console.h"

using namespace std;
using namespace NeuralNet;
using namespace NeuralNet::Activations;

int main(int argc, char* argv[]) {

	Debug::timestamp_display(true);

	// Create model
	Debug::info("Creating model");
	Model model;

	// Add input layer
	model.add_layer(new InputLayer(10));

	// Add some hidden layers with various default activations
	model.add_layer(new HiddenLayer(512, ActivationType::SIGMOID));
	model.add_layer(new HiddenLayer(256, ActivationType::RELU, "ReLU layer"));
	model.add_layer(new HiddenLayer(128, ActivationType::SIGMOID));
	model.add_layer(new HiddenLayer(64, ActivationType::SIGMOID));
	model.add_layer(new HiddenLayer(32, ActivationType::SIGMOID));
	
	// Add output layer
	model.add_layer(new OutputLayer(5));

	// Show model description
	model.describe();

	// Compile model
	Debug::info("Compiling model");
	model.compile();

	// Show model description
	model.describe();

	// Dispose model
	Debug::info("Disposing model");
	model.dispose();

	// Show model description
	model.describe();

	return 0;
}
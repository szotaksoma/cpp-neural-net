#include <csignal>
#include "NeuralNet.h"

using namespace std;
using namespace NeuralNet;
using namespace NeuralNet::Activations;

int signum = 0;
bool killed = false;

void signalHandler(int sig) {
	 signum = sig;
   killed = true;
}

int main(int argc, const char** argv) {

	signal(SIGINT, signalHandler);
	WeightInitializers::set_seed(1234);

	vector<double> test_input;
	for(int i = 0; i < 32; i++) {
		test_input.push_back((double)i / 32.0);
	}

	Model* m = new Model("Test model");
	m->add_layer(new InputLayer(32));
	m->add_layer(new HiddenLayer(128, ActivationType::RELU));
	m->add_layer(new HiddenLayer(128, ActivationType::RELU));
	m->add_layer(new HiddenLayer(128, ActivationType::RELU));
	m->add_layer(new OutputLayer(10));
	m->compile();
	m->describe();
	vector<double> test_output = m->evaluate(test_input);
	for(double d : test_output) {
		Debug::info("Output: " + Debug::to_fixed(d), true);
	}
	Debug::info("Disposing model");
	delete m;
	if(killed) { 
		Debug::error("Process interrupted, exiting");
		exit(signum);
	}

	return 0;
}
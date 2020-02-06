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

	Args::parse(argc, argv);
	Debug::suppress_errors(Args::have("--no-errors"));

	signal(SIGINT, signalHandler);
	WeightInitializers::set_seed(1234);

	vector<double> test_input;
	for(int i = 0; i < 784; i++) {
		test_input.push_back((double)i / 784.0);
	}

	Model* m = new Model("Test model");
	m->add_layer(new InputLayer(784));
	m->add_layer(new HiddenLayer(512, ActivationType::RELU));
	m->add_layer(new HiddenLayer(368, ActivationType::RELU));
	m->add_layer(new HiddenLayer(168, ActivationType::RELU));
	m->add_layer(new HiddenLayer(96, ActivationType::RELU));
	m->add_layer(new HiddenLayer(32, ActivationType::RELU));
	m->add_layer(new OutputLayer(10));
	m->compile();
	m->describe();
	vector<double> test_output = m->evaluate(test_input);
	Debug::info("Output:", true);
	for(double d : test_output) {
		Debug::info(Debug::to_fixed(d), true);
	}
	Debug::info("Disposing model");
	delete m;
	if(killed) { 
		Debug::error("Process interrupted, exiting");
		exit(signum);
	}

	return 0;
}
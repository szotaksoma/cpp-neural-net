#include <csignal>
#include "core/activations.h"
#include "core/model.h"
#include "util/debug.h"

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
	Debug::enable_timestamp(true);

	for(int i = 0; i < 32; i++) {
		Debug::info("Running test #" + to_string(i + 1));
		Model* m = new Model("Model #" + to_string(i + 1));
		m->add_layer(new InputLayer(16));
		for(int l = 0; l < i; l++) {
			m->add_layer(new HiddenLayer((l+1) * 64, ActivationType::RELU));
		}
		m->add_layer(new OutputLayer(4));
		m->compile();
		m->describe();
		Debug::info("Disposing model");
		delete m;
		if(killed) {
   		Debug::error("Process interrupted, exiting");
			exit(signum);
		}
	}

	return 0;
}
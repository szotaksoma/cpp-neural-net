#include <csignal>
#include "core/activations.h"
#include "core/model.h"
#include "util/console.h"

using namespace std;
using namespace NeuralNet;
using namespace NeuralNet::Activations;

int signum = 0;
bool killed = false;

void signalHandler(int sig) {
	 signum = sig;
   killed = true;
}

int main(int argc, char* argv[]) {

	signal(SIGINT, signalHandler); 
	Debug::timestamp_display(true);

	for(int i = 0; i < 32; i++) {
		Model* m = new Model("Test model");
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
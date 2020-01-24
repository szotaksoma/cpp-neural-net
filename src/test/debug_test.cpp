#include "NeuralNet.h"

using namespace std;
using namespace NeuralNet;

int main(int argc, const char** argv) {

	Args::parse(argc, argv);

	if(Args::have("--debug"))
		Debug::suppress_errors(false);

	// Default behaviour
	Debug::info("Some debug informaton.");
	Debug::error("An error occurred during some process.");

	// Display timestamp
	Debug::enable_timestamp(true);
	Debug::info("Some debug informaton.");
	Debug::error("An error occurred during some process.");

	// Do not display timestamp
	Debug::enable_timestamp(false);
	Debug::info("Some debug information.");
	Debug::error("An error occurred during some process.");
	
	return 0;

}
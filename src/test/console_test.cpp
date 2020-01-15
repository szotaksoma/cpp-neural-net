#include "util/console.h"

using namespace std;
using namespace NeuralNet;

int main(int argc, char* argv[]) {

	// Default behaviour
	Debug::info("(test) Some debug informaton.");
	Debug::error("(test) An error occurred during some process.");

	// Display timestamp
	Debug::timestamp_display(true);
	Debug::info("(test) Some debug informaton.");
	Debug::error("(test) An error occurred during some process.");

	// Do not display timestamp
	Debug::timestamp_display(false);
	Debug::info("(test) Some debug information.");
	Debug::error("(test) An error occurred during some process.");
	
	return 0;
}
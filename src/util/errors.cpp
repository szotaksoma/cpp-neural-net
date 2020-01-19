#include <string>
#include "util/console.h"
#include "util/errors.h"

using namespace std;
using namespace NeuralNet;

runtime_error Errors::model_compile_error(string message) {
	string out = "Model compilation failed: " + message;
	Debug::error(out);
	return runtime_error(out);
}

runtime_error Errors::layer_initialize_error(string message) {
	string out = "Layer initialization failed: " + message;
	Debug::error(out);
	return runtime_error(out);
}

runtime_error Errors::layer_does_not_exist_error(string message) {
	string out = "Layer does not exist: " + message;
	Debug::error(out);
	return runtime_error(out);
}
#include <string>
#include "util/console.h"
#include "util/errors.h"

using namespace std;
using namespace NeuralNet;

runtime_error Errors::model_compile_error(const char* message) {
	return model_compile_error(string(message));
}

runtime_error Errors::model_compile_error(string message) {
	string out = string("Model compilation failed: ").append(message);
	Debug::error(out);
	return runtime_error(out);
}

runtime_error Errors::layer_initialize_error(const char* message) {
	return layer_initialize_error(string(message));
}

runtime_error Errors::layer_initialize_error(string message) {
	string out = string("Layer initialization failed: ").append(message);
	Debug::error(out);
	return runtime_error(out);
}

runtime_error Errors::layer_does_not_exist_error(const char* message) {
	return layer_does_not_exist_error(string(message));
}

runtime_error Errors::layer_does_not_exist_error(string message) {
	string out = string("Layer does not exist: ").append(message);
	Debug::error(out);
	return runtime_error(out);
}
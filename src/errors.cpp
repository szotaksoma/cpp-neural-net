#include <string>
#include "util/errors.h"

using namespace std;
using namespace NeuralNet::Errors;

runtime_error model_compile_error(const char* message) {
	return std::runtime_error(string("Model compilation failed: ").append(message));
}

runtime_error layer_initialize_error(const char* message) {
	return std::runtime_error(string("Layer initialization failed: ").append(message));
}

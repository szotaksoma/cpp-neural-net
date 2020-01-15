#include <string>
#include "util/console.h"
#include "util/errors.h"

using namespace std;
using namespace NeuralNet;
using namespace NeuralNet::Errors;

runtime_error model_compile_error(const char* message) {
	Debug::error(message);
	return std::runtime_error(string("Model compilation failed: ").append(message));
}

runtime_error layer_initialize_error(const char* message) {
	Debug::error(message);
	return std::runtime_error(string("Layer initialization failed: ").append(message));
}

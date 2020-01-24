#include <string>
#include "util/debug.h"
#include "util/errors.h"

#define CONDITIONAL_THROW if (!Debug::_suppress_errors) throw

using namespace std;
using namespace NeuralNet;

void Errors::Model::compile_error(string message) {
	string out = "Model compilation failed: " + message;
	Debug::error(out);

	CONDITIONAL_THROW runtime_error(out);
}

void Errors::Layer::initialize_error(string message) {
	string out = "Layer initialization failed: " + message;
	Debug::error(out);

	CONDITIONAL_THROW runtime_error(out);
}

void Errors::Layer::does_not_exist_error(string message) {
	string out = "Layer does not exist: " + message;
	Debug::error(out);

	CONDITIONAL_THROW runtime_error(out);
}

void Errors::Frame::already_has_key(string message) {
	string out = "Frame already has key: " + message;
	Debug::error(out);

	CONDITIONAL_THROW runtime_error(out);
}
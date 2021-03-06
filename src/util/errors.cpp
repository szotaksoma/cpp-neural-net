#include <string>
#include "NeuralNet.h"

#define CONDITIONAL_THROW(message) if (!Debug::_suppress_errors) throw runtime_error(message);

using namespace std;
using namespace NeuralNet;

void Errors::Model::compile_error(string message) {
	string out = "Model compilation failed: " + message;
	Debug::error(out);

	CONDITIONAL_THROW (out);
}

void Errors::Model::not_compiled(string message) {
	string out = "Model is not compiled: " + message;
	Debug::error(out);

	CONDITIONAL_THROW (out);
}

void Errors::Model::unmatching_dimensions(string message) {
	string out = "Data dimensionality does not match input layer: " + message;
	Debug::error(out);

	CONDITIONAL_THROW (out);
}

void Errors::Layer::initialize_error(string message) {
	string out = "Layer initialization failed: " + message;
	Debug::error(out);

	CONDITIONAL_THROW (out);
}

void Errors::Layer::does_not_exist_error(string message) {
	string out = "Layer does not exist: " + message;
	Debug::error(out);

	CONDITIONAL_THROW (out);
}

void Errors::Frame::already_has_key(string message) {
	string out = "Frame already has key: " + message;
	Debug::error(out);

	CONDITIONAL_THROW (out);
}

void Errors::Frame::does_not_have_key(string message) {
	string out = "Frame does not have key: " + message;
	Debug::error(out);

	CONDITIONAL_THROW (out);
}

void Errors::Frame::index_out_of_range(string message) {
	string out = "Frame does not have column with index: " + message;
	Debug::error(out);

	CONDITIONAL_THROW (out);
}

void Errors::Series::index_out_of_range(string message) {
	string out = "Series index out of range: " + message;
	Debug::error(out);

	CONDITIONAL_THROW (out);
}
#ifndef _ERRORS
#define _ERRORS

#include <string>
#include <stdexcept>

namespace NeuralNet::Errors {

	// Cannot compile model
	std::runtime_error model_compile_error(std::string);

	// Cannot initialize unbound layer
	std::runtime_error layer_initialize_error(std::string);

	// Layer does not exist
	std::runtime_error layer_does_not_exist_error(std::string);

}

#endif // !_ERRORS
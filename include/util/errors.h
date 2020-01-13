#ifndef _ERRORS
#define _ERRORS

#include <stdexcept>

namespace NeuralNet::Errors {

	// Cannot compile model
	std::runtime_error model_compile_error(const char*);

	// Cannot initialize unbound layer
	std::runtime_error layer_initialize_error(const char*);

}

#endif // !_ERRORS
#ifndef _ERRORS
#define _ERRORS

#include <string>
#include <stdexcept>

namespace NeuralNet::Errors {

	namespace Model {
		// Cannot compile model
		std::runtime_error compile_error(std::string);
	}

	namespace Layer {
		// Cannot initialize unbound layer
		std::runtime_error initialize_error(std::string);

		// Layer does not exist
		std::runtime_error does_not_exist_error(std::string);
	}

	namespace Frame {
		// Layer does not exist
		std::runtime_error already_has_key(std::string);
	}

}

#endif // !_ERRORS
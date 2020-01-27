#ifndef _ERRORS
#define _ERRORS

#include <string>
#include <stdexcept>

namespace NeuralNet::Errors {

	namespace Model {
		// Cannot compile model
		void compile_error(std::string);
	}

	namespace Layer {
		// Cannot initialize unbound layer
		void initialize_error(std::string);

		// Layer does not exist
		void does_not_exist_error(std::string);
	}

	namespace Frame {
		// Frame already has key
		void already_has_key(std::string);
		// Frame does not have key
		void does_not_have_key(std::string);
	}

	namespace Series {
		// Series index out of range
		void index_out_of_range(std::string);
	}

}

#endif // !_ERRORS
#ifndef _NAMABLE
#define _NAMABLE

#include <string>

namespace NeuralNet {
	class Namable {
		public:
			// Get object name
			std::string name() {
				return this->_name;
			}
			// Rename object
			void rename(std::string name) {
				this->_name = name;
			}
		private:
			std::string _name;
	};
}

#endif // !_NAMABLE
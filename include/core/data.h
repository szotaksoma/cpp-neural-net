#ifndef _DATA
#define _DATA

#include <string>
#include <vector>
#include <map>

namespace NeuralNet::Data {

	template <typename T>
	class Column {
		public:
			Column(std::string name) {
				this->name = name;
				this->values = new std::vector<T>();
			}
			~Column() {
				delete this->values;
			}
			std::string name;
			std::vector<T>* values;
	};

}

#endif // !_DATA
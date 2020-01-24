#ifndef _DATA
#define _DATA

#include <string>
#include <vector>
#include <map>

#include "util/namable.h"
#include "util/errors.h"
#include "util/debug.h"

namespace NeuralNet::Data {

	class ISeries : public Namable {};

	template <typename T>
	class Series : public ISeries {

		public:
			std::vector<T>* values;

			Series(std::string name = "Unnamed series") {
				this->rename(name);
				this->values = new std::vector<T>();
			}

			~Series() {
				delete this->values;
			}

	};

	class Frame : public Namable {
		
		public:
			std::map<std::string, ISeries*> data;

			Frame(std::string name = "Unnamed frame") {
				this->rename(name);
			}

			~Frame() {
				for(std::pair<std::string, ISeries*> p : data) {
					delete p.second;
				}
			}

			void add(ISeries* series) {
				if(data.find(series->name()) == data.end()) {
					data[series->name()] = series;
				} else {
					Errors::Frame::already_has_key(name() + ": " + series->name());
				}
			}

	};

}

#endif // !_DATA
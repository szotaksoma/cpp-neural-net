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

			Series(std::string name) {
				this->rename(name);
				this->values = new std::vector<T>();
			}

			~Series() {
				delete this->values;
			}

			void from_array(T* values, const std::size_t length) {
				this->values->clear();
				for(std::size_t i = 0; i < length; i++) {
					this->values->push_back(values[i]);
				}
			}

			void head(std::size_t n = 10) {
				if(values->size() < n) {
					n = values->size();
				}
				Debug::horizontal_divider();
				Debug::info("First " + std::to_string(n) + " elements of '" + name() + "'", true);
				Debug::info("", true);
				Debug::info("index\tvalue", true);
				for(std::size_t i = 0; i < n; i++) {
					Debug::info(std::to_string(i) + "\t" + std::to_string(values->at(i)), true);
				}
				Debug::horizontal_divider();
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
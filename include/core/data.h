#ifndef _DATA
#define _DATA

#include <string>
#include <vector>
#include <map>
#include <tuple>

#include "util/namable.h"
#include "util/errors.h"
#include "util/debug.h"

namespace NeuralNet::Data {

	class Series : public Namable {

		public:
			std::vector<double> values;

			Series(std::string name);

			double operator[](std::size_t index);
			void from_array(double* values, const std::size_t length);
			void from_vector(std::vector<double> &vector);
			void head(std::size_t n = 10);
			std::tuple<std::size_t, std::size_t> size();

	};

	class Frame : public Namable {
		
		public:
			std::map<std::string, Series> data;

			Frame(std::string name = "Unnamed frame");
			
			void add(Series series);
			Series operator[] (std::string key);
			void head(std::size_t n = 10);
			std::tuple<std::size_t, std::size_t> size();

	};

}

#endif // !_DATA
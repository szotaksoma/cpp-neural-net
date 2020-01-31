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
			Series(std::string name);

			double operator[](std::size_t index);
			void from_array(double* values, const std::size_t length);
			void from_vector(std::vector<double> &vector);
			void head(std::size_t n = 10);
			std::tuple<std::size_t, std::size_t> size();

		protected:
			std::vector<double> values;
			friend class Frame;

	};

	class Frame : public Namable {
		
		public:
			std::map<std::string, Series> data;

			Frame(std::string name = "Unnamed frame");
			
			void add(Series series);
			Series operator[] (std::string key);
			std::vector<double> row(std::size_t index);
			std::vector<double> next_row();
			void reset_row_index();
			void head(std::size_t n = 10);
			std::tuple<std::size_t, std::size_t> size();

		private:
			std::size_t row_count = 0;
			std::size_t index = 0;
	};

}

#endif // !_DATA
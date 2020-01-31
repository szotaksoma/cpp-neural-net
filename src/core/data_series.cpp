#include "core/data.h"

using namespace std;
using namespace NeuralNet::Data;

Series::Series(string name) {
	this->rename(name);
}

double Series::operator[](size_t index) {
	if(values.size() > index) {
		return values[index];
	} else {
		Errors::Series::index_out_of_range(name() + ": " + to_string(index));
		return 0.0;
	}
}

void Series::from_array(double* values, const size_t length) {
	this->values.clear();
	for(size_t i = 0; i < length; i++) {
		this->values.push_back(values[i]);
	}
}

void Series::from_vector(vector<double> &vector) {
	this->values = vector;
}

void Series::head(size_t n) {
	if(values.size() < n) {
		n = values.size();
	}
	Debug::horizontal_divider();
	Debug::info("First " + std::to_string(n) + " elements of '" + name() + "'", true);
	Debug::info("", true);
	Debug::set_style_bold();
	Debug::info("index\tvalue", true);
	Debug::reset_style();
	for(size_t i = 0; i < n; i++) {
		Debug::info(to_string(i) + "\t" + Debug::to_fixed(values[i]), true);
	}
	Debug::horizontal_divider();
}

tuple<size_t, size_t> Series::size() {
	return tuple<size_t, size_t>(values.size(), 1);
}

#include "core/data.h"

using namespace std;
using namespace NeuralNet::Data;

Series::Series(string name) {
	Debug::info("Series ctor called: " + this->name());
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

void Series::head(size_t n) {
	if(values.size() < n) {
		n = values.size();
	}
	Debug::horizontal_divider();
	Debug::info("First " + std::to_string(n) + " elements of '" + name() + "'", true);
	Debug::info("", true);
	Debug::info("index\tvalue", true);
	for(size_t i = 0; i < n; i++) {
		Debug::info(to_string(i) + "\t" + to_string(values[i]), true);
	}
	Debug::horizontal_divider();
}


Frame::Frame(string name) {
	this->rename(name);
}

void Frame::add(Series series) {
	if(data.find(series.name()) == data.end()) {
		data.insert(make_pair(series.name(), series));
	} else {
		Errors::Frame::already_has_key(name() + ": " + series.name());
	}
}

Series Frame::operator[] (string key) {
	if(data.find(key) != data.end()) {
		return data.at(key);
	} else {
		return Series("");
		Errors::Frame::does_not_have_key(name() + ": " + key);
	}
}
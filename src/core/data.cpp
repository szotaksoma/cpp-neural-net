#include "core/data.h"

using namespace NeuralNet;
using namespace NeuralNet::Data;

Series::Series(std::string name) {
	Debug::info("Series ctor called");
	this->rename(name);
	this->values = new std::vector<double>();
}

Series::~Series() {
	Debug::info("Series dtor called");
	delete this->values;
}

double Series::operator[](std::size_t index) {
	if(values->size() > index) {
		return values->at(index);
	} else {
		Errors::Series::index_out_of_range(name() + ": " + std::to_string(index));
		return 0.0;
	}
}

void Series::from_array(double* values, const std::size_t length) {
	this->values->clear();
	for(std::size_t i = 0; i < length; i++) {
		this->values->push_back(values[i]);
	}
}

void Series::head(size_t n) {
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

Frame::Frame(std::string name) {
	this->rename(name);
}

Frame::~Frame() {
	/*for(std::pair<std::string, Series> p : data) {
		delete p.second;
	}*/
}

void Frame::add(Series series) {
	if(data.find(series.name()) == data.end()) {
		data[series.name()] = series;
	} else {
		Errors::Frame::already_has_key(name() + ": " + series.name());
	}
}

Series Frame::operator[] (std::string key) {
	if(data.find(key) != data.end()) {
		return data[key];
	} else {
		return Series("");
		Errors::Frame::does_not_have_key(name() + ": " + key);
	}
}

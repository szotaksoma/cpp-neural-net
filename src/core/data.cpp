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
	return tuple<size_t, size_t>(values.size(), 1ul);
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

void Frame::head(size_t n) {
	if(get<0>(data.begin()->second.size()) < n) {
		n = get<0>(data.begin()->second.size());
	}
	Debug::horizontal_divider();
	Debug::info("First " + std::to_string(n) + " rows of '" + name() + "'", true);
	Debug::info("", true);
	string header = "index";
	for(pair<string, Series> p : data) {
		header += "\t" + p.second.name();
	}
	Debug::set_style_bold();
	Debug::info(header, true);
	Debug::reset_style();
	string row;
	for(size_t i = 0; i < n; i++) {
		row = to_string(i);
		for(pair<string, Series> p : data) {
			row += "\t"+ Debug::to_fixed(p.second[i]);
		}
		Debug::info(row, true);
	}
	Debug::horizontal_divider();
}

tuple<size_t, size_t> Frame::size() {
	const size_t row_count = get<0>(data.begin()->second.size());
	return tuple<size_t, size_t>(row_count, data.size());
}
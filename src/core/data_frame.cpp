#include "core/data.h"

using namespace std;
using namespace NeuralNet::Data;

template <typename T>
bool contains(map<string, T> collection, string value) {
	return !(collection.find(value) == collection.end());
}

Frame::Frame(string name) {
	this->rename(name);
	this->row_count = 0;
	this->index = 0;
}

void Frame::add(Series series) {
	if(data_map.find(series.name()) == data_map.end()) {
		row_count = get<0>(series.size());
		data_map.insert(make_pair(series.name(), series));
		data_vector.push_back(series);
	} else {
		Errors::Frame::already_has_key(name() + ": " + series.name());
	}
}

Series Frame::operator[] (string key) {
	if(contains(data_map, key)) {
		return data_map.at(key);
	} else {
		Errors::Frame::does_not_have_key(name() + ": " + key);
		return Series("");
	}
}

Series Frame::operator[] (size_t index) {
	if(data_vector.size() > index) {
		return data_vector.at(index);
	} else {
		Errors::Frame::index_out_of_range(name() + ": " + to_string(index));
		return Series("");
	}
}

vector<double> Frame::row(size_t index) {
	vector<double> r;
	for(Series s : data_vector) {
		r.push_back(s[index]);
	}
	return r;
}

void Frame::reset_row_index() {
	index = 0;
}

vector<double> Frame::next_row() {
	vector<double> r = row(index);
	index++;
	if(index >= row_count) {
		reset_row_index();
	}
	return r;
}

void Frame::head(size_t n) {
	if(row_count < n) {
		n = row_count;
	}
	Debug::horizontal_divider();
	Debug::info("First " + std::to_string(n) + " rows of '" + name() + "'", true);
	Debug::info("", true);
	string header = "index";
	for(Series s : data_vector) {
		header += "\t" + s.name();
	}
	Debug::set_style_bold();
	Debug::info(header, true);
	Debug::reset_style();
	string row;
	for(size_t i = 0; i < n; i++) {
		row = to_string(i);
		for(Series s : data_vector) {
			row += "\t"+ Debug::to_fixed(s[i]);
		}
		Debug::info(row, true);
	}
	Debug::horizontal_divider();
}

tuple<size_t, size_t> Frame::size() {
	const size_t row_count = get<0>(data_vector[0].size());
	return tuple<size_t, size_t>(row_count, data_vector.size());
}

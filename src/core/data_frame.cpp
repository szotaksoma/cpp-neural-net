#include "core/data.h"

using namespace std;
using namespace NeuralNet::Data;

Frame::Frame(string name) {
	this->rename(name);
}

void Frame::add(Series series) {
	if(data.find(series.name()) == data.end()) {
		row_count = get<0>(series.size());
		data.insert(make_pair(series.name(), series));
	} else {
		Errors::Frame::already_has_key(name() + ": " + series.name());
	}
}

Series Frame::operator[] (string key) {
	if(data.find(key) != data.end()) {
		return data.at(key);
	} else {
		Errors::Frame::does_not_have_key(name() + ": " + key);
		return Series("");
	}
}

vector<double> Frame::row(size_t index) {
	vector<double> r;
	for(pair<string, Series> p : data) {
		r.push_back(p.second[index]);
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

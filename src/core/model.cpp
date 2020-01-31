#include <iomanip>
#include "NeuralNet.h"

using namespace NeuralNet;
using namespace std;

Model::Model(string name) {
	this->rename(name);
}

Model::~Model() {
	this->dispose();
}

bool Model::is_compiled() {
	return this->_compiled;
}

bool Model::is_disposed() {
	return this->_disposed;
}

void Model::add_layer(Layer* layer) {
	layers.push_back(layer);
}

unsigned int Model::layer_count() {
	return (unsigned int)layers.size();
}

Layer* Model::get_layer(unsigned int index) {
	if(layers.size() > index) {
		return layers[index];
	}
	Errors::Layer::does_not_exist_error("index '" + to_string(index) + "'");
	return nullptr;
}

Layer* Model::get_layer(string name) {
	for(Layer* layer : layers) {
		if(layer->name().compare(name) == 0) {
			return layer;
		}
	}
	Errors::Layer::does_not_exist_error("name '" + name + "'");
	return nullptr;
}

void Model::compile() {
	if(layers.size() < 2) {
		Errors::Model::compile_error("Model must have at least 2 layers");
	}
	if(_compiled) {
		Debug::info("Model already compiled");
	}
	// bind layers
	layers[0]->bind(nullptr, layers[1]);
	for(int i = 1; i < (int)layers.size() - 1; i++) {
		layers[i]->bind(layers[i - 1], layers[i + 1]);
	}
	layers[layers.size() - 1]->bind(layers[layers.size() - 2], nullptr);
	for(Layer* layer : layers) {
		layer->initialize();
	}
	_compiled = true;
	_disposed = false;
}



string format_allocated_memory_string(unsigned long bytes) {
	double b = (double) bytes;
	if(b > 1e9) {
		return Debug::to_fixed(b / (1024.0 * 1024.0 * 1024.0)) + " GiB";
	}
	if(b > 1e6) {
		return Debug::to_fixed(b / (1024.0 * 1024.0)) + " MiB";
	}
	if(b > 1e3) {
		return Debug::to_fixed(b / 1024.0) + " KiB";
	}
	return to_string(bytes) + " bytes";
}

void Model::describe() {
	if(_disposed) {
		Debug::info("Model has been disposed");
		return;
	}
	n_params = 0;
	n_trainable_params = 0;
	allocated_memory = 0;
	unsigned int layer_params;
	for(int i = 0; i < (int)layers.size(); i++) {
		layer_params = 0;
		// biases + values
		layer_params += layers[i]->size;
		// values (non-trainable)
		n_params += layers[i]->size;
		if(i > 0) {
			// weights
			layer_params += layers[i]->size * layers[i-1]->size;
		}
		n_params += layer_params;
		if(layers[i]->trainable) {
			n_trainable_params += layer_params;
		}
		allocated_memory += sizeof(*(layers[i]->activation));
	}
	if(_compiled) {
		allocated_memory += sizeof(double) * n_params;
	}
	Debug::horizontal_divider();
	Debug::info("Model summary", true);
	Debug::info(" Name: " + name(), true);
	Debug::info(" Parameters:\t\t" + to_string(n_params), true);
	Debug::info(" Trainable parameters:\t" + to_string(n_trainable_params), true);
	Debug::info(" Allocated memory:\t" + format_allocated_memory_string(allocated_memory), true);
	Debug::info("", true);
	Debug::info("Model structure", true);
	Debug::info(" Layers:\t\t" + to_string(layers.size()), true);
	for(int i = 0; i < (int)layers.size(); i++) {
		Debug::info("  #" + to_string(i + 1) + "\t" + layers[i]->describe(), true);
	}
	Debug::horizontal_divider();
}

void Model::dispose() {
	_compiled = false;
	_disposed = true;
	for(Layer* layer : layers) {
		delete layer;
	}
	layers.clear();
}
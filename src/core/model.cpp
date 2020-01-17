#include "core/model.h"
#include "util/console.h"
#include "util/errors.h"

using namespace NeuralNet;
using namespace std;

void Model::add_layer(Layer* layer) {
	layers.push_back(layer);
}

void Model::compile() {
	if(layers.size() < 2) {
		throw Errors::model_compile_error("Model must have at least 2 layers.");
	}
	if(compiled) {
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
	compiled = true;
	disposed = false;
}

const char* Model::get_name() {
	return this->name;
}

void Model::set_name(const char* name) {
	this->name = name;
}

void Model::describe() {
	if(disposed) {
		Debug::info("Model has been disposed");
		return;
	}
	n_params = 0;
	n_trainable_params = 0;
	allocated_memory = 0;
	unsigned int layer_params;
	for(int i = 0; i < (int)layers.size(); i++) {
		layer_params = 0;
		// biases
		layer_params += layers[i]->size;
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
	if(compiled) {
		allocated_memory += sizeof(double) * n_params;
	}
	Debug::horizontal_divider();
	Debug::info("Model summary", true);
	Debug::info(string(" Parameters:\t\t") + to_string(n_params), true);
	Debug::info(string(" Trainable parameters:\t") + to_string(n_trainable_params), true);
	Debug::info(string(" Allocated memory:\t") + to_string(allocated_memory) + " bytes", true);
	Debug::info("", true);
	Debug::info("Model structure", true);
	Debug::info(string(" Layers:\t\t") + to_string(layers.size()), true);
	for(int i = 0; i < (int)layers.size(); i++) {
		Debug::info(string("  #") + to_string(i + 1) + "\t" + layers[i]->describe(), true);
	}
	Debug::horizontal_divider();
}

void Model::dispose() {
	compiled = false;
	disposed = true;
	for(Layer* layer : layers) {
		delete layer;
	}
	layers.clear();
}
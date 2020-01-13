#include "model.h"

using namespace NeuralNet;
using namespace std;

void Model::add_layer(Layer layer) {
	layers.push_back(layer);
}

void Model::build() {
	if(layers.size() < 2) {
		// TODO: raise exception
		// Model must have at least 2 layers (input & output)
		return;
	}
	// Attach layers
	layers[0].bind(nullptr, &layers[1]);
	for(int i = 1; i < layers.size() - 1; i++) {
		layers[i].bind(&layers[i - 1], &layers[i + 1]);
	}
	layers[layers.size() - 1].bind(&layers[layers.size() - 2], nullptr);
	for(Layer layer : layers) {
		layer.initialize();
	}
}

void Model::describe() {

}
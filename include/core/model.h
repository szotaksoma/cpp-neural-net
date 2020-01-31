#ifndef _MODEL
#define _MODEL

#include "core/layers.h"
#include "util/namable.h"
#include <string>
#include <vector>

// TODO implement:
// get_input(), get_output(), feed_forward(), evaluate() in "model.cpp"

namespace NeuralNet {

	class Model : public Namable {

		public:
			Model(std::string name = "Unnamed model");
			~Model();
			bool is_compiled();
			bool is_disposed();
			// Print model description to console
			void describe();
			// Add a new layer to the model
			void add_layer(Layer*);
			// Get number of layers for model
			unsigned int layer_count();
			// Get model layer by index
			Layer* get_layer(unsigned int index);
			// Get model layer by name
			Layer* get_layer(std::string name);
			// Get input (first) layer of the model
			Layer* get_input();
			// Get output (last) layer of the model
			Layer* get_output();
			// Compile current model structure
			void compile();
			// Feed data forward through the model
			void feed_forward(std::vector<double> iv);
			// Evaluate model output at given input data
			std::vector<double> evaluate(std::vector<double>);
			// Free resources used by model
			void dispose();

			std::vector<Layer*> layers;
			unsigned long n_params;
			unsigned long n_trainable_params;
			unsigned long allocated_memory;
		
		private:
			bool _compiled = false;
			bool _disposed = false;

	};

}

#endif // !_MODEL
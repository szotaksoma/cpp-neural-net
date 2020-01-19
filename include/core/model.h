#ifndef _MODEL
#define _MODEL

#include "core/layers.h"
#include <string>
#include <vector>

namespace NeuralNet {

	class Model {

		public:
			Model(std::string name = "Unnamed model");
			~Model();
			bool is_compiled();
			bool is_disposed();
			// Get model name
			std::string name();
			// Rename model
			void rename(std::string);
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
			// Compile current model structure
			void compile();
			// Free resources used by model
			void dispose();

			std::vector<Layer*> layers;
			unsigned long n_params;
			unsigned long n_trainable_params;
			unsigned long allocated_memory;
		
		private:
			bool _compiled = false;
			bool _disposed = false;
			std::string _name;

	};

}

#endif // !_MODEL
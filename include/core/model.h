#ifndef _MODEL
#define _MODEL

#include "core/layers.h"
#include <vector>

namespace NeuralNet {

	class Model {

		public:
			Model(const char* name = "Unnamed model");
			~Model();
			bool is_compiled();
			bool is_disposed();
			// Get model name
			const char* name();
			// Rename model
			void rename(const char*);
			// Print model description to console
			void describe();
			// Add a new layer to the model
			void add_layer(Layer*);
			// Get number of layers for model
			unsigned int layer_count();
			// Get model layer by index
			Layer* get_layer(unsigned int index);
			// Get model layer by name
			Layer* get_layer(const char* name);
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
			const char* _name;

	};

}

#endif // !_MODEL
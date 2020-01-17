#ifndef _MODEL
#define _MODEL

#include "core/layers.h"
#include <vector>

namespace NeuralNet {

	class Model {

		public:
			std::vector<Layer*> layers;
			// Add a new layer to the model
			void add_layer(Layer*);
			// Compile current model structure
			void compile();
			// Get model name
			const char* get_name();
			// Set model name
			void set_name(const char*);
			// Print model description to console
			void describe();
			// Free resources used by model
			void dispose();

			unsigned long n_params;
			unsigned long n_trainable_params;
			unsigned long allocated_memory;
		
		private:
			bool compiled = false;
			bool disposed = false;
			const char* name;

	};

}

#endif // !_MODEL
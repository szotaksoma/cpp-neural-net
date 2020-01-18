#ifndef _LAYER
#define _LAYER

#include <string>
#include "core/activations.h"

namespace NeuralNet {

	enum LayerType {
		INPUT, HIDDEN, OUTPUT
	};
	
	class Layer {

		public:
			unsigned int size;
			bool trainable;
			double** weights;
			double* biases;
			double* values;
			LayerType type;
			Activations::Activation* activation;
			// Get layer name
			const char* name();
			// Rename layer
			void rename(const char* name);
			std::string describe();
			~Layer();

		protected:
			void initialize();
			void bind(Layer* previous, Layer* next);
			const char* _name;
			Layer* next = nullptr;
			Layer* previous = nullptr;
			bool bound = false;

			friend class Model;

	};

	class InputLayer : public Layer {
		public:
			InputLayer(unsigned int size, const char* name = "Input layer");
	};

	class HiddenLayer : public Layer {
		public:
			HiddenLayer(unsigned int size, Activations::ActivationType, const char* name = "Hidden layer");
			HiddenLayer(unsigned int size, Activations::Activation*, const char* name = "Hidden layer");
	};

	class OutputLayer : public Layer {
		public:
			OutputLayer(unsigned int size, const char* name = "Output layer");
	};

}

#endif // !_LAYER
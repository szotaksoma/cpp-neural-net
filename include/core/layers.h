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
			std::string name();
			// Rename layer
			void rename(std::string name);
			std::string describe();
			~Layer();

		protected:
			void initialize();
			void bind(Layer* previous, Layer* next);
			std::string _name;
			Layer* next = nullptr;
			Layer* previous = nullptr;
			bool bound = false;

			friend class Model;

	};

	class InputLayer : public Layer {
		public:
			InputLayer(unsigned int size, std::string name = "Input layer");
	};

	class HiddenLayer : public Layer {
		public:
			HiddenLayer(unsigned int size, Activations::ActivationType, std::string name = "Hidden layer");
			HiddenLayer(unsigned int size, Activations::Activation*, std::string name = "Hidden layer");
	};

	class OutputLayer : public Layer {
		public:
			OutputLayer(unsigned int size, std::string name = "Output layer");
	};

}

#endif // !_LAYER
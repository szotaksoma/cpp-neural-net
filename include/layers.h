#ifndef _LAYER
#define _LAYER

#include "model.h"
#include "activations.h"

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

		protected:
			void initialize();
			void bind(Layer* previous, Layer* next);
			Layer* next = nullptr;
			Layer* previous = nullptr;
			bool bound = false;

			friend class Model;

	};

	class InputLayer : Layer {
		public:
			InputLayer(unsigned int);
			void initialize();
	};

	class HiddenLayer : Layer {
		public:
			HiddenLayer(unsigned int, Activations::ActivationType);
	}

	class OutputLayer : Layer {
		public:
			OutputLayer(unsigned int);
	};

}

#endif // !_LAYER
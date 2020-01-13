#ifndef _LAYER
#define _LAYER

#include "core/model.h"
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
			~Layer();

		protected:
			void initialize();
			void bind(Layer* previous, Layer* next);
			Layer* next = nullptr;
			Layer* previous = nullptr;
			bool bound = false;

			friend class Model;

	};

	class InputLayer : public Layer {
		public:
			InputLayer(unsigned int);
			void initialize();
	};

	class HiddenLayer : public Layer {
		public:
			HiddenLayer(unsigned int, Activations::ActivationType);
	};

	class OutputLayer : public Layer {
		public:
			OutputLayer(unsigned int);
	};

}

#endif // !_LAYER
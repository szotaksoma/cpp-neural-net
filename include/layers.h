#ifndef _LAYER
#define _LAYER

#include "model.h"
#include "activations.h"

namespace NeuralNet {

	enum LayerType {
		Input, Hidden, Output
	};
	
	class Layer {

		public:
			unsigned int size;
			bool trainable;
			double** weights;
			double* biases;
			double* values;
			LayerType type;
			Layer* next;
			Layer* previous;
			Activations::Activation* activation;

		private:
			friend class Model;
			void set_next(Layer*);
			void set_previous(Layer*);

	};

	class InputLayer : Layer {
		public:
			InputLayer(unsigned int);
	};

	class HiddenLayer : Layer {
		public:
			HiddenLayer(unsigned int, Activations::ActivationType);
	}

	class OutputLayer : Layer {

	};

}

#endif // !_LAYER
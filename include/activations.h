#ifndef _ACTIVATIONS
#define _ACTIVATIONS

#include <math.h>

namespace NeuralNet::Activations {

	class Activation {
		public:
			// Activation function
			virtual double function(double) = 0;
			// Derivative of activation function
			virtual double derivative(double) = 0;
	};

	class Linear : public Activation {

		public:
			// Default constructor
			Linear();
			// Parametric constructor
			Linear(double);
			double function(double);
			double derivative(double);

		private:
			constexpr static double default_m = 1.0;
			// Slope
			double m;

	};

	class ReLU : public Activation {
		public:
			double function(double);
			double derivative(double);
	};

	class TanH : public Activation {
		public:
			double function(double);
			double derivative(double);
	};

	class Sigmoid : public Activation {
		public:
			double function(double);
			double derivative(double);
	};

}

#endif // !_ACTIVATIONS
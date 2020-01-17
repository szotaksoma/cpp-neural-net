#ifndef _ACTIVATIONS
#define _ACTIVATIONS

namespace NeuralNet::Activations {

	enum ActivationType {
		LINEAR, RELU, TANH, SIGMOID
	};

	class Activation {
		public:
			// Activation function
			virtual double function(double) = 0;
			// Derivative of activation function
			virtual double derivative(double) = 0;
			// Description
			ActivationType type;
			const char* name;
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
			ReLU();
			double function(double);
			double derivative(double);

	};

	class TanH : public Activation {

		public:
			TanH();
			double function(double);
			double derivative(double);

	};

	class Sigmoid : public Activation {

		public:
			Sigmoid();
			double function(double);
			double derivative(double);
			
	};

	Activation* default_activation(ActivationType);

}

#endif // !_ACTIVATIONS
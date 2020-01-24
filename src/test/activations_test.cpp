#include <iostream>
#include <iomanip>
#include "NeuralNet.h"

using namespace std;
using namespace NeuralNet;

void log_test(double x, double y, double d_y) {
	cout << "[ x = " <<  x << "\tf(x) = " << y << "\tf'(x) = " << d_y << " ]" << endl;
}

Activations::Activation* parse_activation_function(char* arg) {
	switch (arg[0]) {
		case 'l':
			return new Activations::Linear();
			break;
		case 'r':
			return new Activations::ReLU();
			break;
		case 't':
			return new Activations::TanH();
			break;
		case 's':
			return new Activations::Sigmoid();
			break;
		default:
			return new Activations::Linear();
			break;
	}
}

int main(int argc, char* argv[]) {
	if(argc < 4) {
		cout << "Usage: " << argv[0] << " <from> <to> <step> [activation type (l|r|t|s)]" << endl;
		return 1;
	}
	Activations::Activation* act;
	if(argc == 5) {
		act = parse_activation_function(argv[4]);
	} else {
		act = new Activations::Linear();
	}
	cout << fixed << setprecision(3);
	const double from = stod(argv[1]);
	const double to = stod(argv[2]);
	double step = stod(argv[3]);
	for(double x = from; x <= to; x += step) {
		log_test(x, act->function(x), act->derivative(x));
	}
	delete act;
	return 0;
}
#include "NeuralNet.h"

using namespace std;
using namespace NeuralNet;
using namespace NeuralNet::Data;

int main(int argc, const char** argv) {

	int even[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};

	Series<int>* series_a = new Series<int>("even");
	series_a->from_array(even, sizeof(even)/sizeof(even[0]));

	series_a->head();
	series_a->head(2);
	series_a->head(20);
	series_a->head(0);

	delete series_a;
	return 0;

}
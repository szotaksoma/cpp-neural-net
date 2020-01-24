#include "core/data.h"
#include "util/args.h"

using namespace std;
using namespace NeuralNet;

int main(int argc, const char** argv) {

	int even[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};

	Data::Series<int>* series_a = new Data::Series<int>("even");
	series_a->from_array(even, sizeof(even)/sizeof(even[0]));

	series_a->head();
	series_a->head(2);
	series_a->head(20);
	series_a->head(0);

	delete series_a;
	return 0;

}
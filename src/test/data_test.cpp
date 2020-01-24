#include "core/data.h"
#include "util/args.h"

using namespace std;
using namespace NeuralNet;

int main(int argc, const char** argv) {

	Data::Series<int>* series_a = new Data::Series<int>("Series A");

	delete series_a;
	return 0;

}
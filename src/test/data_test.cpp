#include "NeuralNet.h"

using namespace std;
using namespace NeuralNet;
using namespace NeuralNet::Data;

int main(int argc, const char** argv) {

	Args::parse(argc, argv);
	if(Args::have("--no-errors")) {
		Debug::suppress_errors(true);
	}

	double numbers[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};

	Series series = Series("numbers");
	series.from_array(numbers, sizeof(numbers)/sizeof(numbers[0]));

	Frame df;
	df.add(series);

	df["numbers"].head();
	Debug::info(to_string(df["numbers"][2]));

	return 0;

}
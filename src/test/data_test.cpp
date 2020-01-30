#include "NeuralNet.h"
#define SERIES_SIZE 1000

using namespace std;
using namespace NeuralNet;
using namespace NeuralNet::Data;

// Fill vector 'v' with 'size' multiples of 'step'
void fill_vector(vector<double> &v, double step, size_t size) {
	v.clear();
	v.resize(size);
	for(size_t i = 0; i < size; i++) {
		v[i] = (double)(i + 1) * step;
	}
}

int main(int argc, const char** argv) {

	Args::parse(argc, argv);
	if(Args::have("--no-errors")) {
		Debug::suppress_errors(true);
	}

	vector<double> twos;
	vector<double> threes;
	fill_vector(twos, 2.0, SERIES_SIZE);
	fill_vector(threes, 3.0, SERIES_SIZE);

	Series s1 = Series("2_multi");
	Series s2 = Series("3_multi");

	s1.from_vector(twos);
	s2.from_vector(threes);

	Frame df;
	df.add(s1);
	df.add(s2);

	df["2_multi"].head(200);
	df["3_multi"].head(200);
	Debug::info(to_string(df["2_multi"][5]));

	return 0;

}
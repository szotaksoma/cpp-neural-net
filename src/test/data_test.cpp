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
	vector<double> fives;
	fill_vector(twos, 2.0, SERIES_SIZE);
	fill_vector(threes, 3.0, SERIES_SIZE);
	fill_vector(fives, 5.0, SERIES_SIZE);

	Series s1 = Series("2s");
	Series s2 = Series("3s");
	Series s3 = Series("5s");

	s1.from_vector(twos);
	s2.from_vector(threes);
	s3.from_vector(fives);

	Frame df = Frame("numbers");
	df.add(s1);
	df.add(s2);
	df.add(s3);

	Debug::info("Direct access");
	Debug::info(to_string(df["2s"][5]));
	Debug::info("Series::head()");
	df["3s"].head();
	Debug::info("Frame::head()");
	df.head();
	Debug::info("Frame::size()");
	Debug::info(to_string(get<0>(df.size())) + ", " + to_string(get<1>(df.size())));

	return 0;

}
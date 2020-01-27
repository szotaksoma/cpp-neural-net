#include "NeuralNet.h"

using namespace std;
using namespace NeuralNet;
using namespace NeuralNet::Data;

int main(int argc, const char** argv) {

	Args::parse(argc, argv);
	if(Args::have("--no-errors")) {
		Debug::suppress_errors(true);
	}

	double twos[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
	double threes[] = {3, 6, 9, 12, 15, 18, 21, 24, 27, 30};

	Series s1 = Series("2's multiples");
	Series s2 = Series("3's multiples");

	s1.from_array(twos, sizeof(twos) / sizeof(twos[0]));
	s2.from_array(threes, sizeof(threes) / sizeof(threes[0]));

	Frame df;
	df.add(s1);
	df.add(s2);

	df["2's multiples"].head();
	df["3's multiples"].head();
	Debug::info(to_string(df["2's multiples"][5]));

	return 0;

}
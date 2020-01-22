#include "core/data.h"
#include "util/args.h"

using namespace std;
using namespace NeuralNet;

int main(int argc, const char** argv) {

	Args::parse(argc, argv);

	if(Args::have("--debug")) {
		Debug::enable_debug_messages(true);
	}

	Data::Series<int>* series_a = new Data::Series<int>("Series A");

	delete series_a;
	return 0;

}
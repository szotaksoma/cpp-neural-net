#include <algorithm>
#include "util/args.h"

using namespace std;
using namespace NeuralNet;

void Args::parse(int argc, const char** argv) {
	for(int i = 0; i < argc; i++) {
		Args::args.push_back(string(argv[i]));
	}
}

bool Args::have(string arg) {
	return find(Args::args.begin(), Args::args.end(), arg) != Args::args.end();
}
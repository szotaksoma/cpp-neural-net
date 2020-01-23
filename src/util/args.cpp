#include <algorithm>
#include "util/args.h"

using namespace std;
using namespace NeuralNet;

vector<string> Args::args;

void Args::parse(int argc, const char** argv) {
	for(int i = 0; i < argc; i++) {
		args.push_back(string(argv[i]));
	}
}

bool Args::have(string arg) {
	return find(args.begin(), args.end(), arg) != args.end();
}
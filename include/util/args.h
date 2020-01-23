#ifndef _ARGS
#define _ARGS

#include <vector>
#include <string>

namespace NeuralNet::Args {
	extern std::vector<std::string> args;
	void parse(int argc, const char** argv);
	bool have(std::string arg);
}

#endif // !_ARGS
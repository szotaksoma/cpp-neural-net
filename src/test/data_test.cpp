#include "core/data.h"
#include "util/console.h"

using namespace std;
using namespace NeuralNet;
using namespace NeuralNet::Data;

int main(int argc, const char** argv) {
	Column<int>* c = new Column<int>("Template test");
	Debug::info("Column name: " + c->name);
	delete c;
	return 0;
}
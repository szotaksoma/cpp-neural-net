#ifndef _DEBUG
#define _DEBUG

#include <string>

namespace NeuralNet::Debug {
	
	void info(std::string, bool hide_timestamp = false);
	void debug(std::string);
	void error(std::string);
	void horizontal_divider();

	// Enable or disable timestamp display for console output
	void enable_timestamp(bool);

	// Enable or disable 'debug' messages
	void enable_debugging(bool);

	extern bool debugging;
	extern bool timestamp;

}

#endif // !_DEBUG
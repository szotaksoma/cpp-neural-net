#ifndef _DEBUG
#define _DEBUG

#include <string>

namespace NeuralNet::Debug {
	
	void info(std::string, bool hide_timestamp = false);

	void error(std::string);
	void horizontal_divider();

	// Enable or disable timestamp display for console output
	void enable_timestamp(bool);

	// Suppress exceptions (only write to console)
	void suppress_errors(bool);

	std::string to_fixed(double, unsigned length = 2);
	std::string pretty_memory(unsigned long bytes);
	void set_style_bold();
	void reset_style();

	extern bool _suppress_errors;
	extern bool _timestamp;

}

#endif // !_DEBUG
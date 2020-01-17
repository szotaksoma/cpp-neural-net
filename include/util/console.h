#ifndef _CONSOLE
#define _CONSOLE

#include <string>

namespace NeuralNet {
	
	class Debug {

		public:
			static void info(const char*, bool hide_timestamp = false);
			static void info(std::string, bool hide_timestamp = false);
			static void error(const char*);
			static void error(std::string);
			static void horizontal_divider();
			// Enable or disaple timestamp display for console output
			static void timestamp_display(bool);

	};

}

#endif // !_CONSOLE
#ifndef _CONSOLE
#define _CONSOLE

#include <string>

namespace NeuralNet {
	
	class Debug {

		public:
			static void info(std::string, bool hide_timestamp = false);
			static void debug(std::string);
			static void error(std::string);
			static void horizontal_divider();
			// Enable or disable timestamp display for console output
			static void enable_timestamp_display(bool);
			// Enable or disable 'debug' messages
			static void enable_debug_messages(bool);

	};

}

#endif // !_CONSOLE
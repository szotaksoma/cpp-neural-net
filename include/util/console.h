#ifndef _CONSOLE
#define _CONSOLE

#include <string>

namespace NeuralNet {
	
	class Debug {

		public:
			static void info(const char*);
			static void info(std::string);
			static void error(const char*);
			static void error(std::string);
			// Enable or disaple timestamp display for console output
			static void timestamp_display(bool);

	};

}

#endif // !_CONSOLE
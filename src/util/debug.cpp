#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include "NeuralNet.h"

#define LINE_WIDTH 64
#define STYLE_RESET "\033[0m"
#define STYLE_BOLD "\033[1m"
#define STYLE_INVERSE "\033[7m"
#define STYLE_RED "\033[31m"
#define STYLE_YELLOW "\033[33m"
#define STYLE_RED_BOLD "\033[31;1m"
#define STYLE_YELLOW_BOLD "\033[33;1m"

using namespace std;
using namespace NeuralNet;

// Namespace globals
bool Debug::_suppress_errors = false;
bool Debug::_timestamp = true;

// Local declarations
void show_timestamp();

// Library functions
void Debug::info(string message, bool hide_timestamp) {
	if(_timestamp && !hide_timestamp)
		show_timestamp();
	cout << message << endl;
}

void Debug::error(string message) {
	cout << STYLE_RED_BOLD;
	if(_timestamp)
		show_timestamp();
	cout << message << endl;
	cout << STYLE_RESET;
}

void Debug::horizontal_divider() {
	for(int i = 0; i < LINE_WIDTH; i++) {
		cout << "-";
	}
	cout << endl;
}

string Debug::to_fixed(double n, unsigned length) {
	ostringstream s;
	s << fixed << setprecision(length) << n;
	return s.str();
}

void Debug::set_style_bold() {
	cout << STYLE_BOLD;
}

void Debug::reset_style() {
	cout << STYLE_RESET;
}

void Debug::enable_timestamp(bool enable) {
	_timestamp = enable;
}

void Debug::suppress_errors(bool enable) {
	_suppress_errors = enable;
}

// Local functions
void show_timestamp() {
	time_t now = time(0);
	tm* ltm = localtime(&now);
	cout << "[" << setfill('0') << setw(2) << ltm->tm_hour <<
					":" << setfill('0') << setw(2) << ltm->tm_min <<
					":" <<  setfill('0') << setw(2) << ltm->tm_sec << "] ";
}
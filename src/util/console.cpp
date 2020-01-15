#include <iostream>
#include <iomanip>
#include <ctime>
#include "util/console.h"

using namespace std;
using namespace NeuralNet;

static const char* STYLE_RESET = "\033[0m";
static const char* STYLE_INVERSE = "\033[7m";
static const char* STYLE_RED = "\033[31m";
static const char* STYLE_YELLOW = "\033[33m";
static const char* STYLE_RED_BOLD = "\033[31;1m";
static const char* STYLE_YELLOW_BOLD = "\033[33;1m";
static bool show_time = false;

void show_timestamp() {
	time_t now = time(0);
	tm* ltm = localtime(&now);
	cout << "[" << ltm->tm_hour <<
					":" << ltm->tm_min <<
					":" << ltm->tm_sec << "] ";
}

void Debug::info(const char* message) {
	info(string(message));
}

void Debug::info(string message) {
	if(show_time)
		show_timestamp();
	cout << message << endl;
}

void Debug::error(const char* message) {
	error(string(message));
}

void Debug::error(string message) {
	cout << STYLE_RED_BOLD;
	if(show_time)
		show_timestamp();
	cout << message << endl;
	cout << STYLE_RESET;
}

void Debug::timestamp_display(bool show) {
	show_time = show;
}
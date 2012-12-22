/*
 * CmdLineParameters.cpp
 *
 *  Created on: Dec 2, 2012
 *      Author: Guillaume Chatelet
 */

#include "CmdLineParameters.h"

#include <stdexcept>
#include <sstream>
#include <cstring>
#include <string>

using namespace std;

template<typename T>
void getArgs(const int argc, char**argv, int &i, T& value) {
	if (i >= argc)
		throw logic_error("missing command line value");
	istringstream iss(argv[i]);
	iss >> value;
	if (iss.fail())
		throw logic_error("bad command line argument type");
	++i;
}

bool matches(const string option, const string shortOption, const string longOption) {
	return option == shortOption || option == longOption;
}

CmdLineParameters::CmdLineParameters(int argc, char**argv) :
		swapBufferInterval(0) {
	for (int i = 1; i < argc; ++i) {
		const char* pOption = argv[i];
		if (matches(pOption, "", "--swapinterval"))
			getArgs(argc, argv, ++i, swapBufferInterval);
		else
			throw logic_error(string("unknown command line argument '") + pOption + "'");
	}
}

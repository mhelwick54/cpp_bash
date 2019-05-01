#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <string>

#define DEBUG 1

template <typename T>
void debug(T msg) {
	if(DEBUG) {
		std::cout << "Debug: " << msg << "\n";
	}
}

#endif

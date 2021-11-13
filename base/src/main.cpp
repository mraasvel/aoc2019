#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <cstdio>

#define FILENAME "input.txt"

int main() {
	std::ifstream file(FILENAME);
	assert(file.is_open());

	std::string line;
	while (std::getline(file, line)) {

	}

	file.close();
	return 0;
}

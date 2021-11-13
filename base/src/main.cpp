#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

#define FILENAME "input.txt"

int main() {
	std::fstream file(FILENAME);
	assert(file.is_open());

	std::string line;
	while (std::getline(file, line)) {

	}

	file.close();
	return 0;
}

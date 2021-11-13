#include <cassert>
#include <fstream>
#include <string>
#include <iostream>

#define FILENAME "input.txt"

int computeP1(int x) {
	return x / 3 - 2;
}

int computeP2(int x) {
	int total = 0;
	while (x != 0) {
		x = x / 3 - 2;
		if (x <= 0) {
			break;
		}
		total += x;
	}
	return total;
}

int main() {

	std::ifstream file(FILENAME);

	assert(file.is_open());

	std::string line;
	int total = 0;
	int totalp2 = 0;

	while (std::getline(file, line)) {
		total += computeP1(std::stoi(line));
		totalp2 += computeP2(std::stoi(line));
	}

	std::cout << total << std::endl;
	std::cout << totalp2 << std::endl;

	file.close();

	return 0;
}

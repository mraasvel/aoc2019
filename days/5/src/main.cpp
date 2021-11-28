#include "util/util.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

#define FILENAME "input.txt"
// #define FILENAME "sample.txt"

/*
1. read file
2. split file
3. convert tokens to int, store in vector
*/

#define TARGET 19690720

#define POSITION 0
#define IMMEDIATE 1

int firstParamMode(int mode) {
	return mode % 10;
}

int secondParamMode(int mode) {
	return (mode / 10) % 10;
}

int thirdParamMode(int mode) {
	return (mode / 100) % 10;
}

// call like tokens, ip + 1, firstParamMode(mode);
int getPosition(std::vector<int> tokens, int index, int mode) {
	if (mode) {
		return index;
	} else {
		return tokens[index];
	}
}

int main() {
	std::ifstream ifs(FILENAME);

	assert(ifs.is_open());

	std::vector<int> tokens;

	std::string line;
	std::getline(ifs, line);
	auto v = util::splitString(line, ',');
	// lambda poggers
	std::for_each(v.begin(), v.end(), [&tokens] (const std::string& x) -> void {
			tokens.push_back(std::stoi(x));
		});
	ifs.close();

	int ip = 0;
	bool cond = true;
	while (cond) {
		tokens[ip];
		int op = tokens[ip] % 100;
		int mode = tokens[ip] / 100;
		switch (op) {
			case 1:
				assert(thirdParamMode(mode) == POSITION);
				tokens[getPosition(tokens, ip + 3, thirdParamMode(mode))]
					= tokens[getPosition(tokens, ip + 1, firstParamMode(mode))]
					+ tokens[getPosition(tokens, ip + 2, secondParamMode(mode))];
				ip += 4;
				break;
			case 2:
				assert(thirdParamMode(mode) == POSITION);
				tokens[getPosition(tokens, ip + 3, thirdParamMode(mode))]
					= tokens[getPosition(tokens, ip + 1, firstParamMode(mode))]
					* tokens[getPosition(tokens, ip + 2, secondParamMode(mode))];
				ip += 4;
				break;
			case 3:
				int n;
				std::cin >> n;
				assert (firstParamMode(mode) == POSITION);
				tokens[getPosition(tokens, ip + 1, firstParamMode(mode))] = n;
				ip += 2;
				break;
			case 4:
				std::cout << tokens[getPosition(tokens, ip + 1, firstParamMode(mode))];
				ip += 2;
				break;
			case 5:
				if (tokens[getPosition(tokens, ip + 1, firstParamMode(mode))]) {
					ip = tokens[getPosition(tokens, ip + 2, secondParamMode(mode))];
				} else {
					ip += 3;
				}
				break;
			case 6:
				if (!tokens[getPosition(tokens, ip + 1, firstParamMode(mode))]) {
					ip = tokens[getPosition(tokens, ip + 2, secondParamMode(mode))];
				} else {
					ip += 3;
				}
				break;
			case 7:
				assert(thirdParamMode(mode) == POSITION);
				if (tokens[getPosition(tokens, ip + 1, firstParamMode(mode))]
					< tokens[getPosition(tokens, ip + 2, secondParamMode(mode))]) {
					tokens[getPosition(tokens, ip + 3, thirdParamMode(mode))] = 1;
				} else {
					tokens[getPosition(tokens, ip + 3, thirdParamMode(mode))] = 0;
				}
				ip += 4;
				break;
			case 8:
				assert(thirdParamMode(mode) == POSITION);
				if (tokens[getPosition(tokens, ip + 1, firstParamMode(mode))]
					== tokens[getPosition(tokens, ip + 2, secondParamMode(mode))]) {
					tokens[getPosition(tokens, ip + 3, thirdParamMode(mode))] = 1;
				} else {
					tokens[getPosition(tokens, ip + 3, thirdParamMode(mode))] = 0;
				}
				ip += 4;
				break;
			default:
				assert(op == 99);
				cond = false;
		}
	}

	printf("\n");
	return 0;
}

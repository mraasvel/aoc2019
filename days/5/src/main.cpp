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

int getMode(int n, int mode) {
	while (n-- > 1) {
		mode /= 10;
	}
	return mode % 10;
}

int getIndex(std::vector<int> tokens, int ip, int index, int mode) {
	if (getMode(index, mode)) {
		return ip + index;
	} else {
		return tokens[ip + index];
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
				tokens[getIndex(tokens, ip, 3, mode)] =
					tokens[getIndex(tokens, ip, 1, mode)] + tokens[getIndex(tokens, ip, 2, mode)];
				ip += 4;
				break;
			case 2:
				tokens[getIndex(tokens, ip, 3, mode)] =
					tokens[getIndex(tokens, ip, 1, mode)] * tokens[getIndex(tokens, ip, 2, mode)];
				ip += 4;
				break;
			case 3:
				int n;
				std::cin >> n;
				tokens[getIndex(tokens, ip, 1, mode)] = n;
				ip += 2;
				break;
			case 4:
				std::cout << tokens[getIndex(tokens, ip, 1, mode)];
				ip += 2;
				break;
			case 5:
				if (tokens[getIndex(tokens, ip, 1, mode)]) {
					ip = tokens[getIndex(tokens, ip, 2, mode)];
				} else {
					ip += 3;
				}
				break;
			case 6:
				if (!tokens[getIndex(tokens, ip, 1, mode)]) {
					ip = tokens[getIndex(tokens, ip, 2, mode)];
				} else {
					ip += 3;
				}
				break;
			case 7:
				if (tokens[getIndex(tokens, ip, 1, mode)]
					< tokens[getIndex(tokens, ip, 2, mode)]) {
					tokens[getIndex(tokens, ip, 3, mode)] = 1;
				} else {
					tokens[getIndex(tokens, ip, 3, mode)] = 0;
				}
				ip += 4;
				break;
			case 8:
				if (tokens[getIndex(tokens, ip, 1, mode)]
					== tokens[getIndex(tokens, ip, 2, mode)]) {
					tokens[getIndex(tokens, ip, 3, mode)] = 1;
				} else {
					tokens[getIndex(tokens, ip, 3, mode)] = 0;
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

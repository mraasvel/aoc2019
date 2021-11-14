#include <fstream>
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

#define FILENAME "input.txt"

std::vector<std::string> split(const std::string& x, char delim) {
	std::vector<std::string> v;

	std::size_t i = x.find_first_not_of(delim, 0);
	while (i < x.size()) {
		std::size_t end = x.find_first_of(delim, i);
		v.push_back(x.substr(i, end - i));
		i = x.find_first_not_of(delim, end);
	}
	return v;
}

/*
1. read file
2. split file
3. convert tokens to int, store in vector
4. run opcode for permutations (x, y) from inclusive range [0, 99]
*/

#define TARGET 19690720

int main() {
	std::ifstream ifs(FILENAME);

	assert(ifs.is_open());

	std::vector<int> opcode;

	std::string line;
	while (std::getline(ifs, line)) {
		auto v = split(line, ',');
		// lambda poggers
		std::for_each(v.begin(), v.end(), [&opcode] (const std::string& x) -> void {
			opcode.push_back(std::stoi(x));
		});
	}
	ifs.close();

	for (int x1 = 0; x1 < 100; ++x1) {
		for (int x2 = 0; x2 < 100; ++x2) {
			std::vector<int> tokens = opcode;
			tokens[1] = x1;
			tokens[2] = x2;
			int ip = 0;
			while (true) {
				tokens[ip];
				int op = tokens[ip];
				if (op == 1) {
					tokens[tokens[ip + 3]] = tokens[tokens[ip + 1]] + tokens[tokens[ip + 2]];
				} else if (op == 2) {
					tokens[tokens[ip + 3]] = tokens[tokens[ip + 1]] * tokens[tokens[ip + 2]];
				} else {
					assert(op == 99);
					if (tokens[0] == TARGET) {
						printf("(%d, %d)\n", x1, x2);
						exit(0);
					}
					break;
				}
				ip += 4;
			}
		}
	}

	return 0;
}

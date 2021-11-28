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
3. convert ops to int, store in vector
*/

#define TARGET 19690720

#define POSITION 0
#define IMMEDIATE 1

class Operations {

public:
	typedef std::vector<int> table_t;

public:
	Operations()
	: ip(0) {}

	int getMode(int n, int mode) const {
		while (n-- > 1) {
			mode /= 10;
		}
		return mode % 10;
	}

	int getIndex(int index, int mode) const {
		if (getMode(index, mode)) {
			return ip + index;
		} else {
			return ops[ip + index];
		}
	}

	void push_back(int n) {
		ops.push_back(n);
	}

	table_t::reference get(int index, int mode) {
		return ops[getIndex(index, mode)];
	}

	void addIp(int n) {
		ip += n;
	}

	void setIp(int n) {
		ip = n;
	}

	int getOp() const {
		return ops[ip];
	}

private:
	table_t ops;
	int ip;
};

int main() {
	std::ifstream ifs(FILENAME);

	assert(ifs.is_open());

	Operations ops;
	std::string line;
	std::getline(ifs, line);
	auto v = util::splitString(line, ',');
	std::for_each(v.begin(), v.end(), [&ops] (const std::string& x) -> void {
			ops.push_back(std::stoi(x));
		});
	ifs.close();

	printf("Start\n");
	while (true) {
		int op = ops.getOp() % 100;
		int mode = ops.getOp() / 100;

		if (op == 1) {
			ops.get(3, mode) = ops.get(1, mode) + ops.get(2, mode);
			ops.addIp(4);
		} else if (op == 2) {
			ops.get(3, mode) = ops.get(1, mode) * ops.get(2, mode);
			ops.addIp(4);
		} else if (op == 3) {
			int input = 5;
			ops.get(1, mode) = input;
			ops.addIp(2);
		} else if (op == 4) {
			std::cout << ops.get(1, mode);
			ops.addIp(2);
		} else if (op == 5) {
			if (ops.get(1, mode)) {
				ops.setIp(ops.get(2, mode));
			} else {
				ops.addIp(3);
			}
		} else if (op == 6) {
			if (!ops.get(1, mode)) {
				ops.setIp(ops.get(2, mode));
			} else {
				ops.addIp(3);
			}
		} else if (op == 7) {
			if (ops.get(1, mode) < ops.get(2, mode)) {
				ops.get(3, mode) = 1;
			} else {
				ops.get(3, mode) = 0;
			}
			ops.addIp(4);
		} else if (op == 8) {
			if (ops.get(1, mode) == ops.get(2, mode)) {
				ops.get(3, mode) = 1;
			} else {
				ops.get(3, mode) = 0;
			}
			ops.addIp(4);
		} else {
			assert(op == 99);
			std::cout << std::endl;
			break;
		}
	}
	return 0;
}

#include "util/util.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <cstdlib>
#include <deque>

// #define FILENAME "input.txt"
#define FILENAME "sample.txt"

/*
1. read file
2. split file
3. convert ops to int, store in vector
*/

#define TARGET 19690720

using namespace std;

#define POSITION 0
#define IMMEDIATE 1

class Operations {

public:
	typedef std::size_t value_type;
	typedef std::vector<value_type> table_t;

public:
	Operations()
	: ip(0) {}

	value_type getMode(value_type n, value_type mode) const {
		while (n-- > 1) {
			mode /= 10;
		}
		return mode % 10;
	}

	value_type getIndex(value_type index, value_type mode) const {
		if (getMode(index, mode)) {
			return ip + index;
		} else {
			return ops[ip + index];
		}
	}

	void push_back(value_type n) {
		ops.push_back(n);
	}

	table_t::reference get(value_type index, value_type mode) {
		return ops[getIndex(index, mode)];
	}

	void addIp(value_type n) {
		ip += n;
	}

	void setIp(value_type n) {
		ip = n;
	}

	value_type getOp() const {
		return ops[ip];
	}

private:
	table_t ops;
	value_type ip;
};

std::string runIntCode(Operations ops, std::size_t phase, std::size_t input, std::vector<int> phases) {
	std::string result;
	bool phase_set = false;
	std::size_t phase_index = 0;
	std::deque<std::size_t> inputs;
	inputs.push_back(input);
	while (true) {
		std::size_t op = ops.getOp() % 100;
		std::size_t mode = ops.getOp() / 100;

		if (op == 1) {
			ops.get(3, mode) = ops.get(1, mode) + ops.get(2, mode);
			ops.addIp(4);
		} else if (op == 2) {
			ops.get(3, mode) = ops.get(1, mode) * ops.get(2, mode);
			ops.addIp(4);
		} else if (op == 3) {
			// std::cout << "INPUT: ";
			// std::cin >> input;
			if (!phase_set) {
				std::cout << "SET PHASE: " << phases[phase_index] << std::endl;
				ops.get(1, mode) = phases[phase_index % phases.size()];
				++phase_index;
				phase_set = true;
			} else {
				std::cout << "SET INPUT: " << inputs.front() << std::endl;
				ops.get(1, mode) = inputs.front();
				inputs.pop_front();
				phase_set = false;
			}
			ops.addIp(2);
		} else if (op == 4) {
			result.append(std::to_string(ops.get(1, mode)));
			input = ops.get(1, mode);
			inputs.push_back(input);
			std::cout << "OUTPUT: " << input << std::endl;
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
			return result;
		}
	}
	return result;
}

// input: 0 1 2 3 4
// all combinations

std::size_t max_val = 0;

void PartOne(std::vector<int> phases, Operations& ops) {
	std::size_t input = 0;
	for (auto phase : phases) {
		std::string result = runIntCode(ops, phase, input, phases);
		// input = std::stoi(result);
		input = std::strtoull(result.c_str(), NULL, 10);
		std::cout << result << std::endl;
	}

	if (input > max_val) {
		std::cout << input << std::endl;
		max_val = input;
	}
}

void PartTwo(std::vector<int> phases, Operations& ops) {
	std::cout << runIntCode(ops, phases[0], 0, phases) << std::endl;
}

bool hasDuplicates(const std::vector<int>& comb) {
	for (std::size_t i = 0; i < comb.size(); ++i) {
		for (std::size_t j = i + 1; j < comb.size(); ++j) {
			if (comb[i] == comb[j]) {
				return true;
			}
		}
	}
	return false;
}

void combinations(std::vector<int>& comb, Operations& ops, int index) {
	for (int i = 5; i < 10; ++i) {
		comb[index] = i;
		if (index != 4) {
			combinations(comb, ops, index + 1);
		} else if (!hasDuplicates(comb)) {
			// for (auto x : comb) {
			// 	std::cout << x << ' ';
			// }
			// std::cout << std::endl;
			PartOne(comb, ops);
		}
	}
}


int main() {
	std::ifstream ifs(FILENAME);

	assert(ifs.is_open());

	Operations ops;
	std::string line;
	std::getline(ifs, line);
	auto v = util::splitString(line, ',');
	std::for_each(v.begin(), v.end(), [&ops] (const std::string& x) -> void {
			ops.push_back(std::strtoull(x.c_str(), NULL, 10));
		});
	ifs.close();

	std::vector<int> comb(5);

	// combinations(comb, ops, 0);
	PartTwo(std::vector<int> {9, 8, 7, 6, 5}, ops);
	// std::cout << max_val << std::endl;
	return 0;
}

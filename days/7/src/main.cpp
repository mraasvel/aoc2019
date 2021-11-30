#include "util/util.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <cstdlib>
#include <deque>

#define FILENAME "input.txt"
// #define FILENAME "sample.txt"

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

	bool phase_set;
	std::size_t phase;
	std::size_t output;

private:
	table_t ops;
	value_type ip;
};

std::size_t max_value = 0;

std::string runIntCode(Operations& ops, std::size_t phase, std::size_t input) {
	std::string result;
	// std::cout << "Running: " << ops.phase << std::endl;
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
			if (!ops.phase_set) {
				// std::cout << "Input (phase): " << ops.phase << std::endl;
				ops.get(1, mode) = ops.phase;
				ops.phase_set = true;
			} else {
				// std::cout << "Input: " << input << std::endl;
				ops.get(1, mode) = input;
			}
			ops.addIp(2);
		} else if (op == 4) {
			result.append(std::to_string(ops.get(1, mode)));
			input = ops.get(1, mode);
			ops.addIp(2);
			ops.output = input;
			return std::to_string(input);
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
			max_value = std::max(input, max_value);
			assert(op == 99);
			// std::cout << input << std::endl;
			return "";
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
		std::string result = runIntCode(ops, phase, input);
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
	std::vector<Operations> amps;

	for (std::size_t i = 0; i < 5; ++i) {
		amps.push_back(ops);
		amps[i].phase_set = false;
		amps[i].phase = phases[i];
	}
	
	std::size_t i = 0;
	std::size_t input = 0;
	while (true) {
		std::string output = runIntCode(amps[i % 5], phases[i % 5], input);
		if (output.empty()) {
			break;
		}
		// std::cout << output << std::endl;
		input = std::stoull(output);
		++i;
	}
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
			// PartOne(comb, ops);
			PartTwo(comb, ops);
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

	combinations(comb, ops, 0);
	// PartTwo(std::vector<int> {9,7,8,5,6}, ops);
	std::cout << max_value << std::endl;
	return 0;
}

#include "util/util.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <unordered_map>

#define FILENAME "input.txt"
// #define FILENAME "sample.txt"

bool isValidPassword(int n) {
	std::string pw(std::to_string(n));

	bool dup = false;
	std::size_t i = 0;
	for (char c = '1'; i < pw.size() && c <= '9'; ++c) {
		int cnt = 0;
		while (i < pw.size() && pw[i] == c) {
			++i;
			++cnt;
		}
		if (cnt == 2) {
			dup = true;
		}
		if (i > 0 && i < pw.size() && pw[i] < pw[i - 1]) {
			return false;
		}
	}

	return dup;
}

int main() {

	assert(isValidPassword(112233));
	assert(!isValidPassword(123444));
	assert(isValidPassword(111122));

	int count = 0;
	for (int i = 193651; i <= 649729; ++i) {
		if (isValidPassword(i)) {
			++count;
		}
	}
	std::cout << count << std::endl;
	return 0;
}

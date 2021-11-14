#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <cstdio>
#include <vector>
#include <unordered_map>

std::vector<std::string> splitString(const std::string& input, char delim)
{
	std::vector<std::string> lines;

	size_t i = input.find_first_not_of(delim);
	while (i < input.length()) {
		size_t end = input.find_first_of(delim, i);
		lines.push_back(input.substr(i, end - i));
		i = input.find_first_not_of(delim, end);
	}
	return lines;
}

#define FILENAME "input.txt"
#define TARGET 19690720

/*
opcode
	[unknown] - error
	[1] - add number from 2 positions and stores in third position
		[1] [x1] [x2] [y] [y] = [x1] + [x2]
	[2] - same as [1] but multiplication
	[99] - exit program

	move forward 4 positions
*/

typedef std::vector<int> TokenType;
typedef int (*OperationType)(std::size_t, TokenType&);

int Op1(std::size_t i, TokenType& tokens) {
	tokens[tokens[i + 3]] = tokens[tokens[i + 1]] + tokens[tokens[i + 2]];
	return 4;
}

int Op2(std::size_t i, TokenType& tokens) {
	tokens[tokens[i + 3]] = tokens[tokens[i + 1]] * tokens[tokens[i + 2]];
	return 4;
}

int Op99(std::size_t i, TokenType& tokens) {
	std::cout << "Op99: " << tokens[0] << std::endl;
	if (tokens[0] == TARGET) {
		exit(0);
	}
	return -1;
}

std::unordered_map<int, OperationType> createMap() {
	std::unordered_map<int, OperationType> m;

	m[1] = Op1;
	m[2] = Op2;
	m[99] = Op99;
	return m;
}

int runOpcode(std::size_t i, TokenType& tokens) {
	static std::unordered_map<int, OperationType> m = createMap();

	if (m.find(tokens[i]) == m.end()) {
		std::cerr << "unknown token: " << tokens[i] << std::endl;
		exit(1);
	}

	return m[tokens[i]](i, tokens);
}

TokenType createTokens(std::vector<std::string> string) {
	TokenType tokens;

	for (auto token : string) {
		tokens.push_back(std::stoi(token));
	}

	return tokens;
}

std::pair<int, int> nextPermutation(std::pair<int, int> p) {
	if (p.second == 99) {
		p.first += 1;
		p.second = 0;
	} else {
		p.second += 1;
	}
	return p;
}

void run(const std::string& content) {
	auto stringTokens = splitString(content, ',');
	TokenType tokens = createTokens(stringTokens);

/*
Part1
	tokens[1] = 12;
	tokens[2] = 2;
*/

	TokenType original_tokens = tokens;
	std::pair<int, int> p = std::make_pair(0, 0);
	while (true) {
		tokens[1] = p.first;
		tokens[2] = p.second;

		std::cout << "Answer: " << p.first * 100 + p.second << std::endl;
		std::size_t i = 0;
		while (true) {
			int result = runOpcode(i, tokens);
			if (result == -1) {
				break;
			}
			i += result;
		}

		p = nextPermutation(p);
		tokens = original_tokens;
	}
}

// int main() {
// 	std::ifstream file(FILENAME);
// 	assert(file.is_open());

// 	std::string line;
// 	std::string content;
// 	while (std::getline(file, line)) {
// 		content.append(line);
// 	}
// 	file.close();

// 	run(content);
// 	return 0;
// }

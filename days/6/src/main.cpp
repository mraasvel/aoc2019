#include "util/util.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>

#define FILENAME "input.txt"
// #define FILENAME "sample.txt"
using namespace std;

struct Body {
	Body()
	: distance(0) {}

	// index 0 is always the body this body orbits
	std::vector<std::string> connected;
	std::string orbits;
	int distance;
};

void PartOne(const std::unordered_map<std::string, Body> bodies) {
	int cnt = 0;
	for (auto x : bodies) {
		std::string val = x.second.orbits;
		++cnt;
		while (val != "COM") {
			if (bodies.find(val) == bodies.end()) {
				break;
			}
			val = bodies.find(val)->second.orbits;
			++cnt;
		}
	}
	std::cout << cnt << std::endl;
}

void PartTwo(std::unordered_map<std::string, Body>& bodies) {
	queue<std::string> targets;

	// simple dijkstra solution
	targets.push(bodies["YOU"].orbits);
	while (!targets.empty()) {
		std::string body = targets.front();
		targets.pop();
		for (auto connection : bodies[body].connected) {
			if (bodies[connection].distance != 0 && bodies[connection].distance < bodies[body].distance) {
				continue;
			}
			targets.push(connection);
			bodies[connection].distance = bodies[body].distance + 1;
		}
	}
	std::cout << bodies[bodies["SAN"].orbits].distance << std::endl;
}

int main() {

	std::unordered_map<std::string, Body> bodies;

	std::ifstream file(FILENAME);
	assert(file.is_open());
	std::string line;
	while (std::getline(file, line)) {
		auto names = util::splitString(line, ')');
		bodies[names[1]].connected.push_back(names[0]);
		bodies[names[1]].orbits = names[0];
		if (names[0] != "COM" && names[1] != "YOU" && names[1] != "SAN") {
			bodies[names[0]].connected.push_back(names[1]);
		}
	}
	file.close();
	PartOne(bodies);
	PartTwo(bodies);
	return 0;
}

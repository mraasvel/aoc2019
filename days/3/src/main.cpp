#include "util/util.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <map>

#define FILENAME "input.txt"
// #define FILENAME "sample.txt"


typedef std::pair<int, int> Point;
struct ComparePoint : std::binary_function<Point, Point, bool> {
	bool operator()(const Point& a, const Point& b) const {
		return a.first < b.first || (a.first == b.first && a.second < b.second);
	}
};
typedef std::set<Point, ComparePoint> PointSetType;

std::unordered_map<char, int> createDX() {
	std::unordered_map<char, int> m;
	m['U'] = 0;
	m['D'] = 0;
	m['R'] = 1;
	m['L'] = -1;
	return m;
}

std::unordered_map<char, int> createDY() {
	std::unordered_map<char, int> m;
	m['U'] = 1;
	m['D'] = -1;
	m['R'] = 0;
	m['L'] = 0;
	return m;
}

static const std::unordered_map<char, int> DX = createDX();
static const std::unordered_map<char, int> DY = createDY();

static std::vector<std::map<Point, std::size_t, ComparePoint>> step_vector;

void CreatePoints(PointSetType& wire, const std::string& line) {
	auto split = util::splitString(line, ',');

	std::map<Point, std::size_t, ComparePoint> step_map;

	Point start(0, 0);
	std::size_t steps = 1;
	for (const auto& cmd : split) {
		char dir = cmd[0];
		int n = std::stoi(cmd.substr(1));

		assert(DX.find(dir) != DX.end());

		for (int i = 0; i < n; ++i) {
			start.first += DX.find(dir)->second;
			start.second += DY.find(dir)->second;
			if (wire.count(start) == 0) {
				wire.insert(start);
				step_map[start] = steps;
			}
			++steps;
		}
	}
	step_vector.push_back(step_map);
}

int MD(const Point& p) {
	return std::abs(p.first) + std::abs(p.second);
}

struct MDComp : public std::binary_function<Point, Point, bool> {
	bool operator()(const Point& a, const Point& b) {
		return MD(a) < MD(b);
	}
};

struct PointCompare : public std::binary_function<Point, Point, bool> {
	bool operator()(const Point& a, const Point& b) {
		return a.first == b.first && a.second == b.second;
	}
};

struct StepCompare : public std::binary_function<Point, Point, bool> {
	bool operator()(const Point& a, const Point& b) {
		return step_vector[2][a] < step_vector[2][b];
	}
};

PointSetType Intersect(const PointSetType& a, const PointSetType& b) {
	PointSetType result;
	std::map<Point, std::size_t, ComparePoint> step_map;
	for (const Point& p : a) {
		if (b.count(p) > 0) {
			step_map[p] = step_vector[0][p] + step_vector[1][p];
			result.insert(p);
		}
	}
	step_vector.push_back(step_map);
	return result;
}

int main() {

	PointSetType W1;
	PointSetType W2;

	std::ifstream file(FILENAME);
	assert(file.is_open());
	std::string line;
	std::getline(file, line);
	CreatePoints(W1, line);
	std::getline(file, line);
	CreatePoints(W2, line);
	file.close();

	PointSetType intersection = Intersect(W1, W2);

	Point r = *std::min_element(intersection.begin(), intersection.end(), MDComp());
	Point r2 = *std::min_element(intersection.begin(), intersection.end(), StepCompare());
	std::cout << "(" << r.first << ", " << r.second << ")" << std::endl;
	std::cout << MD(r) << std::endl;
	std::cout << step_vector[2][r2] << std::endl;

	return 0;
}

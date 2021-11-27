// #include "util/util.hpp"
// #include <iostream>
// #include <fstream>
// #include <string>
// #include <cassert>
// #include <cstdio>
// #include <vector>
// #include <algorithm>
// #include <unordered_map>
// #include <set>

// #define FILENAME "input.txt"
// // #define FILENAME "sample.txt"

// class Point {
// public:
// 	Point()
// 	: x(0), y(0), steps(0) {}
// 	Point(const Point& rhs)
// 	: x(rhs.x), y(rhs.y), steps(rhs.steps) {}
// 	Point(int x, int y)
// 	: x(x), y(y), steps(0) {}

// 	Point& operator=(const Point& p) {
// 		x = p.x;
// 		y = p.y;
// 		steps = p.steps;
// 		return *this;
// 	}

// 	bool operator<(const Point& b) const {
// 		return x < b.x || (x == b.x && y < b.y);
// 	}

// 	bool operator==(const Point& rhs) const {
// 		return x == rhs.x && y == rhs.y;
// 	}

// 	Point operator+(const Point& rhs) const {
// 		return Point(x + rhs.x, y + rhs.y);
// 	}

// 	Point operator-(const Point& rhs) const {
// 		return Point(x - rhs.x, y - rhs.y);
// 	}

// 	Point& operator+=(const Point& rhs) {
// 		x += rhs.x;
// 		y += rhs.y;
// 		return *this;
// 	}

// 	friend std::ostream& operator<<(std::ostream& out, const Point& rhs);

// 	int ManhattanDistance() const {
// 		return std::abs(x) + std::abs(y);
// 	}

// 	void setSteps(std::size_t n) {
// 		steps = n;
// 	}

// 	std::size_t getSteps() const {
// 		return steps;
// 	}

// private:
// 	int x;
// 	int y;
// 	std::size_t steps;
// };

// std::ostream& operator<<(std::ostream& out, const Point& rhs) {
// 	out << "(" << rhs.x << ", " << rhs.y << ")";
// 	return out;
// }

// class Wire {

// public:
// 	typedef std::set<Point> PointSet;
// public:
// 	void Fill(const std::string& line) {
// 		std::vector<std::string> coords = util::splitString(line, ',');

// 		Point p;
// 		std::size_t num_steps = 0;
// 		for (const std::string& coord : coords) {
// 			int value = std::strtol(&coord.c_str()[1], NULL, 10);
// 			for (int i = 0; i < value; ++i) {
// 				switch (coord.front()) {
// 					case 'U':
// 						p += Point(0, 1);
// 						break;
// 					case 'D':
// 						p += Point(0, -1);
// 						break;
// 					case 'R':
// 						p += Point(1, 0);
// 						break;
// 					case 'L':
// 						p += Point(-1, 0);
// 						break;
// 				}
// 				++num_steps;
// 				p.setSteps(num_steps);
// 				points.insert(p);
// 			}
// 		}
// 	}

// 	PointSet::size_type size() const {
// 		return points.size();
// 	}

// 	PointSet::const_iterator begin() const {
// 		return points.begin();
// 	}

// 	PointSet::const_iterator end() const {
// 		return points.end();
// 	}

// 	PointSet::size_type count(const Point& p) const {
// 		return points.count(p);
// 	}

// 	PointSet::const_iterator find(const Point& p) const {
// 		return points.find(p);
// 	}


// private:
// 	PointSet points;
// };

// Wire::PointSet Intersect(const Wire& a, const Wire& b) {
// 	Wire::PointSet result;

// 	for (const auto& p : a) {
// 		if (b.count(p) != 0) {
// 			Point prime = p;
// 			Point intersected = *b.find(p);
// 			prime.setSteps(p.getSteps() + intersected.getSteps());
// 			result.insert(prime);
// 		}
// 	}

// 	return result;
// }

// bool ManhattanDistanceCompare(const Point& a, const Point& b) {
// 	return a.ManhattanDistance() < b.ManhattanDistance();
// }

// bool StepCompare(const Point& a, const Point& b) {
// 	return a.getSteps() < b.getSteps();
// }

// int main() {

// 	Wire wires[2];

// 	std::ifstream file(FILENAME);
// 	assert(file.is_open());
// 	std::string line;
// 	int i = 0;
// 	while (std::getline(file, line)) {
// 		wires[i].Fill(line);
// 		++i;
// 	}
// 	file.close();


// 	std::set<Point> intersections = Intersect(wires[0], wires[1]);

// 	std::cout << "Size1: " << wires[0].size() << std::endl;
// 	std::cout << "Size2: " << wires[1].size() << std::endl;
// 	std::cout << "Intersections: " << intersections.size() << std::endl;

// 	Point result = *std::min_element(intersections.begin(), intersections.end(), &ManhattanDistanceCompare);
// 	Point result2 = *std::min_element(intersections.begin(), intersections.end(), &StepCompare);

// 	std::cout << "Closest intersection: " << result << std::endl;
// 	std::cout << "Distance: " << result.ManhattanDistance() << std::endl;
// 	std::cout << "Reach: " << result2 << " in " << result2.getSteps() << " steps" << std::endl;

// 	return 0;
// }

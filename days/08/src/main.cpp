#include "util/util.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <array>

using namespace std;

constexpr int WIDTH = 25;
constexpr int HEIGHT = 6;
constexpr int LAYER_SIZE = WIDTH * HEIGHT;

struct Layer {
	Layer()
	: num_zeros(0) {}
	int num_zeros;
	std::array<char, LAYER_SIZE> digits;

	size_t computeIndex(size_t x, size_t y) const {
		return y * WIDTH + x;
	}

	void print() const {
		for (size_t y = 0; y < HEIGHT; y++) {
			for (size_t x = 0; x < WIDTH; x++) {
				size_t index = computeIndex(x, y);
				if (digits[index] == '0') {
					std::cout << ' ';
				} else {
					std::cout << "Y";
				}
				// std::cout << digits[y * WIDTH + x];
			}
			std::cout << std::endl;
		}
	}
};

int computeP1(const Layer& layer) {
	size_t c1 = 0;
	size_t c2 = 0;
	std::for_each(layer.digits.begin(), layer.digits.end(), [&c1, &c2] (char x) -> void {
		if (x == '1') {
			c1++;
		} else if (x == '2') {
			c2++;
		}
	});
	return c1 * c2;
}

Layer generateImage(const std::vector<Layer>& layers) {
	Layer result;
	for (size_t i = 0; i < LAYER_SIZE; i++) {
		for (size_t j = 0; j < layers.size(); j++) {
			result.digits[i] = layers[j].digits[i];
			if (result.digits[i] != '2') {
				break;
			}
		}
	}
	return result;
}

// 2(P * L) + P -> O(PL + P) -> O(P(1 + L))
int main(int argc, char *argv[]) {
	assert(argc != 1);
	std::ifstream file(argv[1]);
	assert(file.is_open());
	std::string line;
	std::getline(file, line);
	file.close();

	std::vector<Layer> layers;
	size_t min_index = 0;
	std::size_t i = 0;
	while (i < line.size()) {
		Layer layer;
		for (std::size_t j = 0; j < LAYER_SIZE; j++) {
			layer.digits[j] = line[i];
			if (layer.digits[j] == '0') {
				layer.num_zeros++;
			}
			i++;
		}
		layers.push_back(layer);
		if (layers[min_index].num_zeros > layers.back().num_zeros) {
			min_index = layers.size() - 1;
		}
	}
	std::cout << layers.size() << std::endl;
	std::cout << min_index << std::endl;
	std::cout << "P1: " << computeP1(layers[min_index]) << std::endl;
	Layer result = generateImage(layers);
	result.print();
	return 0;
}

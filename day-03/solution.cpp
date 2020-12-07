#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<std::pair<int, int>> slopes = { {1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2} };

unsigned long long int treesInPath(const std::vector<std::string>& map, int dx, int dy) {
	int x = 0;
	int trees = 0;
	for (int y = 0; y < map.size(); y += dy) {
		if (map[y][x % map[y].size()] == '#') {
			trees++;
		}
		x += dx;
	}
	return trees;
}

int main() {
	std::ifstream input("input-d03.txt");
	std::vector<std::string> map;
	std::string buffer;
	unsigned long long int result = 1;
	while (input >> buffer) {
		map.push_back(buffer);
	}

	for (const std::pair<int, int>& slope : slopes) {
		result *= treesInPath(map, slope.first, slope.second);
	}
	std::cout << result << std::endl;
}
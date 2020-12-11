#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int countSeats(const std::vector<std::string>& map) {
	int seats = 0;
	for (const auto& r : map) {
		for (char c : r) {
			if (c == '#') {
				seats++;
			}
		}
	}
	return seats;
}

char occupiedAround(int r, int c, std::vector<std::string>* map) {
	int occupied = 0;
	for (int i = r - 1; i <= r + 1; ++i) {
		for (int j = c - 1; j <= c + 1; ++j) {
			if (i >= 0 && i < map->size() && j >= 0 && j < (*map)[0].size()
				&& !(i == r && j == c) && (*map)[i][j] == '#') {
				occupied++;
			}
		}
	}
	return occupied;
}

char occupiedDirection(int r, int c, std::vector<std::string>* map) {
	int occupied = 0;
	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			if (i == 0 && j == 0) {
				continue;
			}
			int x = c + i;
			int y = r + j;
			while (y >= 0 && y < map->size() && x >= 0 && x < (*map)[0].size()) {
				if ((*map)[y][x] == '#') {
					occupied++;
					break;
				}
				if ((*map)[y][x] == 'L') {
					break;
				}
				x += i;
				y += j;
			}
		}
	}
	return occupied;
}

char updateCell(int r, int c, char seat, std::vector<std::string>* map) {
	if (seat == '.') {
		return '.';
	}

	int occupied = occupiedDirection(r, c, map);
	if (seat == 'L' && occupied == 0) {
		return '#';
	}
	if (seat == '#' && occupied >= 5) {
		return 'L';
	}
	return seat;
}

void updateToStable(std::vector<std::string>* map) {
	std::vector<std::string> temp(*map);
	temp[0][0] = '1';
	while (true) {
		for (int r = 0; r < map->size(); ++r) {
			for (int c = 0; c < (*map)[r].size(); ++c) {
				temp[r][c] = updateCell(r, c, (*map)[r][c], map);
			}
		}	
		if (temp == *map) {
			break;
		}
		*map = temp;
	}
}

int main() {
	std::ifstream input("input-d11.txt");
	std::string buffer;
	std::vector<std::string> map;

	while (input >> buffer) {
		map.push_back(buffer);
	}

	updateToStable(&map);
	std::cout << countSeats(map) << std::endl;
}

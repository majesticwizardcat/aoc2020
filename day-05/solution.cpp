#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

const int ROWS = 7;
const int COLS = 3;
const int MAX_ROW = 127;
const int MAX_COL = 7;

int binary(int min, int max, int steps, int maxSteps, const std::string& buffer) {
	if (steps == maxSteps - 1) {
		if (buffer[steps] == 'F' || buffer[steps] == 'L') {
			return min;
		}
		else {
			return max;
		}
	}

	if (buffer[steps] == 'F' || buffer[steps] == 'L') {
		return binary(min, (min + max) / 2, steps + 1, maxSteps, buffer);
	}
	else {
		return binary(std::ceil((floor)(max + min) / 2.0f), max, steps + 1, maxSteps, buffer);
	}
}

int getID(const std::string& buffer) {
	int row = binary(1, MAX_ROW - 1, 0, ROWS, buffer);
	int col = binary(0, MAX_COL, 7, 7 + COLS, buffer);
	return row * 8 + col;
}

int main() {
	std::ifstream input("input-d05.txt");
	std::string buffer;
	std::vector<int> ids;

	while (input >> buffer) {
		ids.push_back(getID(buffer));
	}
	std::sort(ids.begin(), ids.end());

	for (int i = 1; i < ids.size(); ++i) {
		if (ids[i] - ids[i - 1] == 2) {
			std::cout << ids[i] - 1 << std::endl;
		}
	}
}
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

int diffs(const std::vector<int>& sortedDevs) {
	int ones = 0;
	int threes = 0;
	int last = 0;
	for (const auto& d : sortedDevs) {
		if (d - last == 1) {
			ones++;
		}
		else if (d - last == 3) {
			threes++;
		}
		last = d;
	}
	return ones * threes;
}

unsigned long long arragments(const std::vector<int>& sortedDevs, int index, std::map<int, unsigned long long>* memo) {
	if (index == sortedDevs.size() - 1) {
		return 1;
	}

	if (memo->find(index) != memo->end()) {
		return (*memo)[index];
	}

	unsigned long long arrs = 0;
	for (int i = index + 1; i <= index + 3 && i < sortedDevs.size(); ++i) {
		if (sortedDevs[i] - sortedDevs[index] <= 3) {
			arrs += arragments(sortedDevs, i, memo);
		}
	}
	(*memo)[index] = arrs;
	return arrs;
}

int main() {
	std::ifstream input("input-d10.txt");
	std::vector<int> devices;
	int in;
	while (input >> in) {
		devices.push_back(in);
	}
	devices.push_back(0);
	std::sort(devices.begin(), devices.end());
	devices.push_back(devices.back() + 3);
	std::map<int, unsigned long long> memo;
	std::cout << arragments(devices, 0, &memo) << std::endl;
}
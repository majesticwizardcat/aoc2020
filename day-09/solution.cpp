#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>

bool checkSum(const std::vector<int>& pre, int n) {
	for (int i = 0; i < pre.size(); ++i) {
		for (int j = i; j < pre.size(); ++j) {
			if (pre[i] + pre[j] == n) {
				return true;
			}
		}
	}
	return false;
}

std::pair<int, int> findMinMax(const std::vector<int>& nums, int n) {
	for (int i = 1; i < nums.size(); ++i) {
		for (int j = 0; j < i; ++j) {
			if (std::accumulate(nums.begin() + j, nums.begin() + i, 0) == n) {
				auto min = std::min_element(nums.begin() + j, nums.begin() + i);
				auto max = std::max_element(nums.begin() + j, nums.begin() + i);
				return std::make_pair(*min, *max);;
			}
		}
	}
	return std::make_pair(-1, -1);
}

int main() {
	std::ifstream input("input-d09.txt");
	std::vector<int> pre;
	std::vector<int> nums;
	int in;

	while (input >> in) {
		if (pre.size() == 25) {
			if (!checkSum(pre, in)) {
				std::pair<int, int> mm = findMinMax(nums, in);
				std::cout << mm.first + mm.second << std::endl;
			}
			pre.erase(pre.begin());
			pre.push_back(in);
		}
		else {
			pre.push_back(in);
		}
		nums.push_back(in);
	}
}
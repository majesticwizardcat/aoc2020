#include <iostream>
#include <map>
#include <vector>

std::vector<int> input = { 0,1,4,13,15,12,16 };
//std::vector<int> input = { 0,3,6 };

int main() {
	std::map<int, std::pair<int, int>> nums;
	int turn = 1;
	int last;

	for (int i : input) {
		nums[i] = std::make_pair(turn, 0);
		turn++;
	}
	last = input.back();

	while (turn <= 30000000) {
		auto spoken = nums.find(last);
		if (spoken != nums.end() && spoken->second.second > 0) {
			last = nums[last].second - nums[last].first;
		}
		else {
			last = 0;
		}

		if (nums.find(last) != nums.end()) {
			if (nums[last].second > 0) {
				nums[last].first = nums[last].second;
				nums[last].second = turn;
			}
			else {
				nums[last].second = turn;
			}
		}
		else {
			nums[last].first = turn;
			nums[last].second = 0;
		}
		turn++;
	}

	std::cout << last << std::endl;
}
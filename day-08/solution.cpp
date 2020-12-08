#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <string>

int findInfinite(const std::vector<std::pair<std::string, int>>& program) {
	std::set<int> visited;
	int accumulator = 0;
	int cur = 0;
	while (true) {
		if (cur == program.size()) {
			return accumulator;
		}
		if (visited.find(cur) != visited.end()) {
			return -1;
		}
		if (program[cur].first == "acc") {
			accumulator += program[cur].second;
			visited.insert(cur);
			cur++;
		}
		else if (program[cur].first == "jmp") {
			visited.insert(cur);
			cur += program[cur].second;
		}
		else {
			cur++;
		}
	}
	return -666;
}

int main() {
	std::ifstream input("input-d08.txt");
	std::string buffer;
	int jumps;
	char symbol;
	std::vector<std::pair<std::string, int>> instructions;

	while (input >> buffer) {
		input.get(symbol);
		input.get(symbol);
		input >> jumps;
		instructions.push_back(std::make_pair(buffer, symbol == '+' ? jumps : -jumps));
	}

	for (auto& i : instructions) {
		if (i.first == "jmp") {
			i.first = "nop";
			int acc = findInfinite(instructions);
			if (acc > 0) {
				std::cout << acc << std::endl;
				return 0;
			}
			i.first = "jmp";
		}
		else if (i.first == "nop") {
			i.first = "jmp";
			int acc = findInfinite(instructions);
			if (acc > 0) {
				std::cout << acc << std::endl;
				return 0;
			}
			i.first = "nop";
		}
	}
}
#include <iostream>
#include <fstream>
#include <vector>

int main() {
	std::ifstream input("input-d011.txt");
	std::vector<int> in;

	if (!input) {
		std::cout << "No input" << std::endl;
		return 1;
	}

	int i;
	while (input) {
		input >> i;
		if (i <= 2020) {
			in.push_back(i);
		}
	}

	for (int i = 0; i < in.size(); ++i) {
		for (int j = i + 1; j < in.size();++j) {
			for (int k = j + 1; k < in.size(); ++k) {
				if (in[i] + in[j] + in[k] == 2020) {
					std::cout << in[i] * in[j] * in[k] << std::endl;
					return 0;
				}
			}
		}
	}
}

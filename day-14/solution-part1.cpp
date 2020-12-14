#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

void updateMasks(const std::string& mask, unsigned long long* andMask,
	unsigned long long* orMask) {
	*andMask = 0;
	*orMask = 0;

	for (char c : mask) {
		*andMask <<= 1;
		*orMask <<= 1;

		if (c == 'X') {
			*andMask += 1;
			*orMask += 0;
		}
		else {
			*andMask += c - '0';
			*orMask += c - '0';
		}
	}
}

unsigned long long getAddress(const std::string& a) {
	char address[1024];
	unsigned int i = 0;
	for (char c : a) {
		if (c >= '0' && c <= '9') {
			address[i] = c;
			i++;
		}
	}
	address[i] = '\0';
	return atoi(address);
}

int main() {
	std::ifstream input("input-d14.txt");
	std::map<unsigned long long, unsigned long long> memory;
	unsigned long long andMask;
	unsigned long long orMask;
	char c;
	std::string buffer;
	
	while (input >> buffer) {
		if (buffer == "mask") {
			input.get(c);
			input.get(c);
			input.get(c);
			input >> buffer;
			updateMasks(buffer, &andMask, &orMask);
		}
		else {
			unsigned long long address = getAddress(buffer);
			unsigned long long value;
			input >> buffer;
			input >> value;
			memory[address] = (value & andMask) | orMask;
		}
	}

	unsigned long long sum = 0;
	for (const auto& v : memory) {
		sum += v.second;
	}
	std::cout << sum << std::endl;
}
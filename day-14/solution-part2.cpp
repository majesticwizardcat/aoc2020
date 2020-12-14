#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <bitset>

void removeX(std::string mask, std::vector<unsigned long long>* addresses) {
	for (int i = 0; i < mask.size(); ++i) {
		if (mask[i] == 'X') {
			mask[i] = '0';
			removeX(mask, addresses);
			mask[i] = '1';
			removeX(mask, addresses);
			return;
		}
	}

	unsigned long long m = 0;
	for (auto c : mask) {
		m <<= 1;
		m += c - '0';
	}
	addresses->push_back(m);
}

std::string getAddress(const std::string& a) {
	std::string address;
	for (char c : a) {
		if (c >= '0' && c <= '9') {
			address  += c;
		}
	}
	std::bitset<36> b(atoi(address.c_str()));
	return b.to_string();
}

void addressesFromMask(const std::string& add, const std::string& mask,
	std::vector<unsigned long long>* addresses) {
	addresses->clear();
	std::string maskedAddress;
	for (int i = 0; i < add.size(); ++i) {
		if (mask[i] == '0') {
			maskedAddress += add[i];
		}
		else if (mask[i] == '1') {
			maskedAddress += '1';
		}
		else {
			maskedAddress += 'X';
		}
	}
	removeX(maskedAddress, addresses);
}

int main() {
	std::ifstream input("input-d14.txt");
	std::map<unsigned long long, unsigned long long> memory;
	std::string mask;
	std::vector<unsigned long long> addresses;
	char c;
	std::string buffer;
	
	while (input >> buffer) {
		if (buffer == "mask") {
			input.get(c);
			input.get(c);
			input.get(c);
			input >> mask;
		}
		else {
			std::string address = getAddress(buffer);
			unsigned long long value;
			input >> buffer;
			input >> value;

			addressesFromMask(address, mask, &addresses);
			for (auto& a : addresses) {
				memory[a] = value;
			}
		}
	}

	unsigned long long sum = 0;
	for (const auto& v : memory) {
		sum += v.second;
	}
	std::cout << sum << std::endl;
}
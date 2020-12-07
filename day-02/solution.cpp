#include <iostream>
#include <fstream>
#include <string>

bool isValid(int min, int max, char c, const std::string& s) {
	int count = 0;
	for (char cs : s) {
		if (cs == c) {
			count++;
		}
	}
	return count >= min && count <= max;
}

bool isValid2(int i0, int i1, char c, const std::string& s) {
	return s[i0 - 1] == c ^ s[i1 - 1] == c;
}

int main() {
	std::ifstream in("input-d02.txt");
	int valid = 0;
	int min = 0;
	int max = 0;
	char l;
	std::string buffer;

	while (in >> min) {
		in.ignore();
		in >> max;
		in >> l;
		in.ignore();
		in >> buffer;
		if (isValid2(min, max, l, buffer)) {
			valid++;
		}
	}

	std::cout << valid << std::endl;
}
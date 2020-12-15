#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

typedef unsigned long long ulong;

ulong next(ulong base, ulong n, ulong diff, ulong incr) {
	while (true) {
		if ((base + diff) % n == 0L) {
			break;
		}
		base += incr;
	}
	return base;
}

int main() {
	std::ifstream input("input-d13.txt");
	ulong buffer;
	char  c;
	ulong diff = 0;
	ulong base;
	ulong incr = 1;
	std::vector<std::pair<int, int>> ids;

	input >> buffer;
	input.get(c);
	input >> base;
	input.get(c);
	diff = 1;
	incr = base;
	while (true) {
		if (input.peek() == EOF) {
			break;
		}
		if (input.peek() >= '0' && input.peek() <= '9') {
			input >> buffer;
			base = next(base, buffer, diff, incr);
			ulong nextBase = next(base + incr, buffer, diff, incr);
			incr = nextBase - base;
			input.get(c);
		}
		else {
			input.get(c);
			input.get(c);
		}
		diff++;
	}
	std::cout << base << std::endl;
}

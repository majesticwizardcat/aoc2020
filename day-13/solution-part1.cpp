#include <iostream>
#include <fstream>
#include <limits>

int findClosest(int from, int n) {
	return from - (from % n) + n;
}

int main() {
	std::ifstream input("input-d13.txt");
	int buffer;
	int min = std::numeric_limits<int>::max();
	int minID;
	int wait;
	char  c;

	input >> wait;
	input.get(c);
	while (true) {
		if (input.peek() == EOF) {
			break;
		}
		if (input.peek() >= '0' && input.peek() <= '9') {
			input >> buffer;

			int next = findClosest(wait, buffer);
			if (next < min) {
				min = next;
				minID = buffer;
			}
			input.get(c);
		}
		else {
			input.get(c);
			input.get(c);
		}
	}
	std::cout << (min - wait) * minID << std::endl;
}

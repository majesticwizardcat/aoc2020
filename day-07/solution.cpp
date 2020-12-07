#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>

struct Bag {
	Bag() { }
	Bag(const Bag& other) : color(other.color), amounts(other.amounts) { }
	std::string color;
	std::map<std::string, int> amounts;
};

int searchBag(const Bag& bag, std::map<std::string, Bag>& bags, std::map<std::string, bool>* looked) {
	for (const auto& holds : bag.amounts) {
		if (holds.first == "shinygold") {
			return 1;
		}
		auto b = looked->find(holds.first);
		if (b == looked->end()) {
			(*looked)[holds.first] = false;
			int found = searchBag(bags[holds.first], bags, looked);
			if (found > 0) {
				(*looked)[holds.first] = true;
				return found + 1;
			}
		}
		else if (b->second) {
			return 1;
		}
	}
	return 0;
}

int shinyHolders(std::map<std::string, Bag>& bags) {
	std::map<std::string, bool> looked;
	looked["shinygold"] = false;
	int holders = 0;
	for (const auto& bag : bags) {
		if (looked.find(bag.first) == looked.end()) {
			looked[bag.first] = false;
			int hol = searchBag(bag.second, bags, &looked);
			if (hol > 0) {
				looked[bag.first] = true;
			}
			holders += hol;
		}
	}
	return holders;
}

int holdsAmount(std::map<std::string, Bag>& bags, const std::string& cur) {
	int amount = 0;
	for (const auto& b : bags[cur].amounts) {
		amount += b.second * holdsAmount(bags, b.first) + b.second;
	}
	return amount;
}

int main() {
	std::ifstream input("input-d07.txt");
	if (!input) {
		std::cout << "No input" << std::endl;
		return 1;
	}
	std::string color0;
	std::string color1;
	std::string buffer;
	char ignore[2050];
	int amount;
	char c;
	std::map<std::string, Bag> bags;

	while (input >> color0) {
		input >> color1;
		Bag b;
		b.color = color0 + color1;
		input >> buffer;
		input >> buffer;
		input.get(c);
		if (input.peek() < '0' || input.peek() > '9') {
			input.getline(ignore, 2050);
			continue;
		}

		else {
			while (true) {
				input >> amount;
				input >> color0;
				input >> color1;
				b.amounts[color0 + color1] = amount;
				input >> buffer;
				if (buffer.back() == '.') {
					break;
				}
			}
		}
		bags[b.color] = b;
	}

	std::cout << holdsAmount(bags, "shinygold") << std::endl;
}
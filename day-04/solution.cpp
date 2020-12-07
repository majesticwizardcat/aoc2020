#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

const int FIELDS_SIZE = 8;
const char* fields[] = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid" };
std::vector<std::string> eyeColors ={ "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };

void reset(std::map<std::string, std::string>* map) {
	for (auto& v : *map) {
		v.second = "";
	}
}

bool checkHeight(const std::string& height) {
	std::string num;
	std::string post;
	for (const auto& c : height) {
		if (c >= '0' && c <= '9') {
			num += c;
		}
		else {
			post += c;
		}
	}
	return (post == "cm" && atoi(num.c_str()) >= 150 && atoi(num.c_str()) <= 193)
		|| (post == "in" && atoi(num.c_str()) >= 59 && atoi(num.c_str()) <= 76);
}

bool checkHair(const std::string& hair) {
	if (hair[0] != '#') {
		return false;
	}
	for (int i = 1; i < hair.size(); ++i) {
		if ((hair[i] >= '0' && hair[i] <= '9')
			|| (hair[i] >= 'a' && hair[i] <= 'f')) {
			continue;
		}
		else {
			return false;
		}
	}
	return true;
}

bool checkEyes(const std::string& eyes) {
	for (const auto& s : eyeColors) {
		if (eyes == s) {
			return true;
		}
	}
	return false;
 }

bool checkArgument(const std::pair<std::string, std::string>& p) {
	if (p.first == "byr") {
		return p.second.size() == 4 && atoi(p.second.c_str()) >= 1920
			&& atoi(p.second.c_str()) <= 2002;
	}
	else if (p.first == "iyr") {
		return p.second.size() == 4 && atoi(p.second.c_str()) >= 2010
			&& atoi(p.second.c_str()) <= 2020;
	}
	else if (p.first == "eyr") {
		return p.second.size() == 4 && atoi(p.second.c_str()) >= 2020
			&& atoi(p.second.c_str()) <= 2030;
	}
	else if (p.first == "hgt") {
		return checkHeight(p.second);
	}
	else if (p.first == "hcl") {
		return checkHair(p.second);
	}
	else if (p.first == "ecl") {
		return checkEyes(p.second);
	}
	else if (p.first == "pid") {
		return p.second.size() == 9;
	}

	std::cout << "BAD" << std::endl;
	return false;
}

bool checkValid(const std::map<std::string, std::string>& checks) {
	for (const auto& v : checks) {
		if (v.second.size() == 0 || !checkArgument(v)) {
			return false;
		}
	}
}

int main() {
	std::ifstream input("input-d04.txt");
	std::map<std::string, std::string> checks;
	std::string buffer;
	std::string field;
	char c;
	int valid = 0;

	for (int i = 0; i < FIELDS_SIZE - 1; ++i) {
		checks[fields[i]] = "";
	}

	while (input.get(c)) {
		if (c == '\n') {
			if (checks.find(field) != checks.end()) {
				checks[field] = buffer;
			}
			buffer.clear();
			input.get(c);
			if (c == '\n') {
				if (checkValid(checks)) {
					valid++;
				}
				reset(&checks);
				continue;
			}
		}

		if (c == ':') {
			field = buffer;
			buffer.clear();
			continue;
		}

		else if (c == ' ') {
			if (checks.find(field) != checks.end()) {
				checks[field] = buffer;
			}
			buffer.clear();
			continue;
		}

		buffer += c;
	}

	std::cout << valid << std::endl;
}

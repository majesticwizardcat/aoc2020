#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

typedef std::pair<int, int> Range;
typedef std::map<std::string, std::pair<Range, Range>> FieldsMap;
typedef std::vector<int> Ticket;
typedef std::map<int, std::set<std::string>> ValidMap;

void parseFields(std::ifstream* input, FieldsMap* fields,
	std::vector<std::string>* fieldNames) {
	char c;
	std::string field;
	int from;
	int to;
	while (true) {
		input->get(c);
		if (c == '\n') {
			break;
		}
		if (c == ':') {
			Range r0;
			Range r1;
			input->get(c);
			*input >> from;
			input->get(c);
			*input >> to;
			r0.first = from;
			r0.second = to;
			for (int i = 0; i < 4; ++i) {
				input->get(c);
			}
			*input >> from;
			input->get(c);
			*input >> to;
			r1.first = from;
			r1.second = to;
			(*fields)[field] = make_pair(r0, r1);
			fieldNames->push_back(field);
			field.clear();
			input->get(c);
		}
		else {
			field += c;
		}
	}
}

bool isInRange(int n, Range r) {
	return n >= r.first && n <= r.second;
}

bool isValid(int n, const FieldsMap& fields) {
	for (auto& f : fields) {
		if (isInRange(n, f.second.first)
			|| isInRange(n, f.second.second)) {
			return true;
		}
	}
	return false;
}

Ticket parseTicket(std::ifstream* input, const FieldsMap& fields) {
	Ticket t;
	int num;
	char c;
	char line[1024];
	while (true) {
		*input >> num;
		if (!isValid(num, fields)) {
			input->getline(line, 1024);
			t.clear();
			break;
		}

		t.push_back(num);
		input->get(c);
		if (c == '\n') {
			break;
		}
	}
	return t;
}

bool validForAll(const std::pair<Range, Range>& range, const std::vector<Ticket>& tickets, int index) {
	for (const auto& t : tickets) {
		if (!isInRange(t[index], range.first)
			&& !isInRange(t[index], range.second)) {
			return false;
		}
	}
	return true;
}

void createValidMap(ValidMap* valid, FieldsMap& fields,
	const std::vector<Ticket>& tickets,
	const std::vector<std::string>& fieldNames) {
	for (int i = 0; i < fieldNames.size(); ++i) {
		for (const auto& field : fieldNames) {
			if (validForAll(fields[field], tickets, i)) {
				(*valid)[i].insert(field);
			}
		}
	}
}

void removeExclusive(ValidMap* valid) {
	bool found = true;
	std::string exclusive;
	std::set<std::string> searched;

	while (found) {
		found = false;
		for (auto& v : *valid) {
			if (v.second.size() == 1
				&& searched.find(*(v.second.begin())) == searched.end()) {
				exclusive = *(v.second.begin());
				found = true;
				break;
			}
		}
		if (!found) {
			break;
		}

		for (auto& v : *valid) {
			if (v.second.size() > 1
				&& v.second.find(exclusive) != v.second.end()) {
				v.second.erase(exclusive);
			}
		}
		searched.insert(exclusive);
	}
}

int main() {
	std::ifstream input("input-d16.txt");
	std::string buffer;
	char c;
	char line[1024];
	int num;
	FieldsMap fields;
	std::vector<Ticket> tickets;
	std::vector<std::string> fieldNames;
	parseFields(&input, &fields, &fieldNames);
	input.getline(line, 1024);

	Ticket myTicket = parseTicket(&input, fields);
	if (myTicket.empty()) {
		std::cout << "Parse error" << std::endl;
	}
	tickets.push_back(myTicket);

	input.getline(line, 1024);
	input.getline(line, 1024);

	while (true) {
		Ticket t = parseTicket(&input, fields);
		if (!t.empty()) {
			tickets.push_back(t);
		}

		if (input.peek() == EOF) {
			break;
		}
	}

	ValidMap valid;
	createValidMap(&valid, fields, tickets, fieldNames);
	removeExclusive(&valid);

	unsigned long long mul = 1L;
	for (const auto& v : valid) {
		if (v.second.begin()->find("departure") != std::string::npos) {
			std::cout << *v.second.begin() << std::endl;
			mul *= (long) myTicket[v.first];
		}
	}
	std::cout << mul << std::endl;
}

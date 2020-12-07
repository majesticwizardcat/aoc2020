#include <iostream>
#include <fstream>

int countYes(bool* answers) {
	int yeses = 0;
	for (int i = 0; i < 26; ++i) {
		if (answers[i]) {
			yeses++;
		}
	}
	return yeses;
}

void reset(bool* a) {
	for (int i = 0; i < 26; ++i) {
		a[i] = false;
	}
}

void setInit(bool* a, std::ifstream* input) {
	char init[27];
	input->getline(init, 27);
	for (int i = 0; i < strlen(init); ++i) {
		a[init[i] - 'a'] = true;
	}
}

void update(bool* a, std::ifstream* input) {
	bool answer[26];
	reset(answer);
	setInit(answer, input);
	for (int i = 0; i < 26; ++i) {
		a[i] = a[i] && answer[i];
	}
}

int main() {
	std::ifstream input("input-d06.txt");
	bool answers[26];
	char c;
	int yeses = 0;

	reset(answers);
	setInit(answers, &input);
	while (input) {
		if (input.peek() == '\n') {
			input.get(c);
			yeses += countYes(answers);
			reset(answers);
			setInit(answers, &input);
		}
		else {
			update(answers, &input);
		}
	}
	yeses += countYes(answers);
	std::cout << yeses << std::endl;
}
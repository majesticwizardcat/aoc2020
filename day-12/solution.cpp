#include <iostream>
#include <fstream>
#include <cmath>

void turn(std::pair<int, int>* direction, int amount) {
	int cosTheta = (int)std::round(std::cos((3.141592f * ((float) -amount / 180.0f))));
	int sinTheta = (int)std::round(std::sin((3.141592f * ((float) -amount / 180.0f))));
	int x = direction->first;
	int y = direction->second;
	direction->first = x * cosTheta - y * sinTheta;
	direction->second = x * sinTheta + y * cosTheta;
}

void move(std::pair<int, int>* location, std::pair<int, int>* direction,
	char type, int amount) {
	switch (type) {
	case 'F':
		location->first += direction->first * amount;
		location->second += direction->second * amount;
		break;
	case 'N':
		location->second += amount;
		break;
	case 'E': 
		location->first += amount;
		break;
	case 'W':
		location->first -= amount;
		break;
	case 'S':
		location->second -= amount;
		break;
	case 'R':
		turn(direction, amount);
		break;
	case 'L':
		turn(direction, -amount);
		break;
	}
}

void moveWaypoint(std::pair<int, int>* location, std::pair<int, int>* waypoint,
	char type, int amount) {
	switch (type) {
	case 'F':
		location->first += waypoint->first * amount;
		location->second += waypoint->second * amount;
		break;
	case 'N':
		waypoint->second += amount;
		break;
	case 'E': 
		waypoint->first += amount;
		break;
	case 'W':
		waypoint->first -= amount;
		break;
	case 'S':
		waypoint->second -= amount;
		break;
	case 'R':
		turn(waypoint, amount);
		break;
	case 'L':
		turn(waypoint, -amount);
		break;
	}
}

int main() {
	std::fstream input("input-d12.txt");
	char type;
	int amount;
	std::pair<int, int> location = std::make_pair(0, 0);
	std::pair<int, int> waypoint = std::make_pair(10, 1);

	while (input >> type) {
		input >> amount;
		moveWaypoint(&location, &waypoint, type, amount);
	}
	std::cout << std::abs(location.first) + std::abs(location.second) << std::endl;
}
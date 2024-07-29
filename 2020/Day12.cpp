#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <sstream>
#include <map>

int getDirection(char direction) // helper function for rotating the ship
{
	switch (direction)
	{
	case 'N': return 0;
	case 'E': return 1;
	case 'S': return 2;
	case 'W': return 3;
	default: return -1;
	}
}

char getDirection(int direction) // helper function for rotating the ship
{
	switch (direction)
	{
	case 0: return 'N';
	case 1: return 'E';
	case 2: return 'S';
	case 3: return 'W';
	default: return 'X';
	}
}

char rotateDirection(char actualDirection, char turningDirection, int rotateAngle)
{
	int tmpDirection = getDirection(actualDirection); // get the current direction
	rotateAngle = (turningDirection == 'R') ? rotateAngle : 4 - rotateAngle; // determine how many quadrants to rotate; rotating one quadrant to the right is the same as rotating three quadrants to the left
	tmpDirection = (tmpDirection + rotateAngle) % 4;
	return getDirection(tmpDirection); // return the new direction
}

void rotateWaypoint(std::pair<int, int>& waypointNS_WE, char turningDirection, int rotateAngle)
{
	rotateAngle = (turningDirection == 'R') ? rotateAngle : 4 - rotateAngle;
	if (rotateAngle == 2) // if rotating 180 degrees, invert the waypoint coordinates
	{
		waypointNS_WE.first = waypointNS_WE.first * (-1);
		waypointNS_WE.second = waypointNS_WE.second * (-1);
	}
	else if (rotateAngle == 1) // if rotating by one quadrant, swap and invert the coordinates accordingly
	{
		int tmpFirst = waypointNS_WE.first;
		int tmpSecond = waypointNS_WE.second;
		waypointNS_WE.first = tmpSecond * (-1);
		waypointNS_WE.second = tmpFirst;
	}
	else if (rotateAngle == 3) // if rotating by three quadrants, swap and invert the coordinates accordingly
	{
		int tmpFirst = waypointNS_WE.first;
		int tmpSecond = waypointNS_WE.second;
		waypointNS_WE.first = tmpSecond;
		waypointNS_WE.second = tmpFirst * (-1);
	}
}

void actionOnMapPartOne(std::pair<int, int>& NS_WE, char& currentDirection, char action, int value)
{
	if (action == 'R' || action == 'L') // rotation
	{
		int rotate = value / 90;
		currentDirection = rotateDirection(currentDirection, action, rotate);
	}
	else
	{
		switch (action) // logic for moving the ship
		{
		case 'N': NS_WE.first += value; break;
		case 'S': NS_WE.first -= value; break;
		case 'E': NS_WE.second += value; break;
		case 'W': NS_WE.second -= value; break;
		case 'F':
			if (currentDirection == 'N') NS_WE.first += value;
			else if (currentDirection == 'S') NS_WE.first -= value;
			else if (currentDirection == 'E') NS_WE.second += value;
			else if (currentDirection == 'W') NS_WE.second -= value;
			break;
		}
	}
}

void actionOnMapPartTwo(std::pair<int, int>& shipNS_WE, std::pair<int, int>& waypointNS_WE, char action, int value)
{
	if (action == 'R' || action == 'L') // rotation
	{
		int rotate = value / 90;
		rotateWaypoint(waypointNS_WE, action, rotate);
	}
	else
	{
		switch (action) // logic for moving the ship and the waypoint
		{
		case 'N': waypointNS_WE.first += value; break;
		case 'S': waypointNS_WE.first -= value; break;
		case 'E': waypointNS_WE.second += value; break;
		case 'W': waypointNS_WE.second -= value; break;
		case 'F': shipNS_WE.first += value * waypointNS_WE.first;
			shipNS_WE.second += value * waypointNS_WE.second; break;
		}
	}
}

int manhattanDistance(const std::pair<int, int>& distance)
{
	return std::abs(distance.first) + std::abs(distance.second);
}

void partOne(const std::vector<std::string>& shipMoves)
{
	char currentDirection = 'E';
	std::pair<int, int> shipNS_WE = { 0, 0 }; // location of our ship. NS directions are .first and WE directions are .second; N+ S- E+ W-  <- increments

	for (const auto& move : shipMoves)
	{
		char action = move[0]; // determine the action to perform
		int valueOfAction = std::stoi(move.substr(1)); // get the value for movement or rotation
		actionOnMapPartOne(shipNS_WE, currentDirection, action, valueOfAction);
	}
	std::cout << "Answer for part 1 -> " << manhattanDistance(shipNS_WE) << '\n';
}

void partTwo(const std::vector<std::string>& shipMoves)
{
	std::pair<int, int> shipNS_WE = { 0,0 }; // same as in part 1
	std::pair<int, int> waypointNS_WE = { 1,10 }; // waypoint location, same increments as in part 1

	for (const auto& move : shipMoves)
	{
		char action = move[0];
		int valueOfAction = std::stoi(move.substr(1));
		actionOnMapPartTwo(shipNS_WE, waypointNS_WE, action, valueOfAction);
	}
	std::cout << "Answer for part 2 -> " << manhattanDistance(shipNS_WE) << '\n';
}

int main()
{
	std::vector<std::string> shipMoves;
	std::ifstream file("data.txt");

	if (!file.is_open())
	{
		std::cerr << "Cannot open the file" << std::endl;
		return 1;
	}

	std::string line;
	while (std::getline(file, line))
	{
		shipMoves.push_back(line);
	}

	partOne(shipMoves);
	partTwo(shipMoves);

	file.close();

	return 0;
}

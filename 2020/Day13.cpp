//#include <iostream>
//#include <fstream>
//#include <string>
//#include <set>
//#include <vector>
//#include <sstream>
//#include <map>
//
//// Function to parse bus IDs from the input data
//std::set<int> parseBuses(const std::vector<std::string>& data)
//{
//	std::set<int> busesID;
//	std::stringstream ss(data[1]);
//	std::string item;
//
//	// Split the second line of data by commas
//	while (std::getline(ss, item, ','))
//	{
//		// If the item is not 'x', convert it to an integer and add to the set
//		if (item != "x")
//		{
//			int number = std::stoi(item);
//			busesID.insert(number);
//		}
//	}
//
//	return busesID;
//}
//
//// Function to find the best bus based on the earliest departure time
//std::pair<int, int> findBestBus(int timeStamp, const std::set<int>& busesID)
//{
//	std::pair<int, int> bestBus;
//	int minTime = INT_MAX;
//
//	// Iterate through each bus ID
//	for (auto& i : busesID)
//	{
//		// Calculate the next departure time for the bus
//		int tmpTime = timeStamp / i;
//		tmpTime = tmpTime * i + i;
//
//		// Update the best bus if the current bus has an earlier departure time
//		if (std::min(minTime, tmpTime - timeStamp) < minTime)
//		{
//			bestBus = { tmpTime - timeStamp, i };
//			minTime = tmpTime - timeStamp;
//		}
//	}
//
//	return bestBus;
//}
//
//// Function to solve part one of the problem
//void partOne(const std::vector<std::string>& data)
//{
//	int timeStamp = stoi(data[0]);
//	std::set<int> busesID = parseBuses(data);
//	std::pair<int, int> bestBus = findBestBus(timeStamp, busesID);
//
//	std::cout << "Answer for part one -> " << bestBus.first * bestBus.second << '\n';
//}
//
//// Function to parse bus IDs with their respective offsets for part two
//std::vector<std::pair<int, int>> addBuses(const std::vector<std::string>& data)
//{
//	std::vector<std::pair<int, int>> busesIDwithTimeStamps; //first is busID, second is the remainder from division
//
//	std::stringstream ss(data[1]);
//	std::string item;
//	int position = 0;
//
//	// Split the second line of data by commas
//	while (std::getline(ss, item, ','))
//	{
//		// If the item is not 'x', convert it to an integer and calculate the offset
//		if (item != "x")
//		{
//			int number = std::stoi(item);
//			busesIDwithTimeStamps.push_back(std::make_pair(number, number - (position % number)));
//		}
//		position++;
//	}
//
//	return busesIDwithTimeStamps;
//}
//
//// Function to solve the Chinese Remainder Theorem for part two
//unsigned long long int chineseRest(const std::vector<std::pair<int, int>>& busesInOrder)
//{
//	unsigned long long int result = 0;
//	unsigned long long int bigN = 1;
//	std::vector<unsigned long long int> inverseModules;
//	std::vector<unsigned long long int> partialBigN;
//
//	// Calculate the product of all bus IDs
//	for (auto& i : busesInOrder)
//	{
//		bigN *= i.first;
//	}
//
//	// Calculate partial products of the bus IDs
//	for (auto& i : busesInOrder)
//	{
//		partialBigN.push_back(bigN / i.first);
//	}
//
//	// Calculate the modular inverses
//	for (int i = 0; i < busesInOrder.size(); i++)
//	{
//		unsigned long long int inverse = 0;
//		int counter = 1;
//		while (1)
//		{
//			if ((partialBigN[i] * counter) % busesInOrder[i].first == 1)
//			{
//				inverse = counter;
//				break;
//			}
//			else
//				counter++;
//		}
//		inverseModules.push_back(inverse);
//	}
//
//	// Calculate the final result using the Chinese Remainder Theorem
//	for (int i = 0; i < busesInOrder.size(); i++)
//	{
//		result += inverseModules[i] * partialBigN[i] * busesInOrder[i].second;
//	}
//
//	return result % bigN;
//}
//
//// Function to solve part two of the problem
//void partTwo(const std::vector<std::string>& data)
//{
//	std::vector<std::pair<int, int>> busesInOrder = addBuses(data);
//	std::cout << "Answer for part two -> " << chineseRest(busesInOrder);
//}
//
//int main()
//{
//	std::vector<std::string> data;
//	std::ifstream file("data.txt");
//
//	// Check if the file is open
//	if (!file.is_open())
//	{
//		std::cerr << "Cannot open the file" << std::endl;
//		return 1;
//	}
//
//	// Read the file line by line
//	std::string line;
//	while (std::getline(file, line))
//	{
//		data.push_back(line);
//	}
//
//	// Solve part one and part two
//	partOne(data);
//	partTwo(data);
//
//	file.close();
//
//	return 0;
//}

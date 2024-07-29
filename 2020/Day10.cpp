//#include <iostream>
//#include <fstream>
//#include <string>
//#include <set>
//#include<vector>
//#include<sstream>
//#include<map>
//
//void partOne(std::set<int>& input);
//void partTwo(std::set<int>& input);
//unsigned long long int recursionForPartTwo(std::set<int>& input, int step, int currentJoltage, int endJoltage, std::map<std::pair<int, int>, unsigned long long int>& paths);
//
//void partOne(std::set<int>& input)
//{
//	int result = 0;
//	int differenceOfOne = 0;
//	int differenceOfThree = 1; //because there is always one differce of 3 joltage in the last adapter and the our device
//
//
//	for (auto& i : input)
//	{
//		if (i - result == 1)
//		{
//			differenceOfOne++;
//			result = i;
//		}
//		else if (i - result == 3)
//		{
//			differenceOfThree++;
//			result = i;
//		}
//	}
//
//	std::cout << "Answer for part one - > " << differenceOfOne * differenceOfThree << '\n';
//}
//
//void partTwo(std::set<int>& input)
//{
//	unsigned long long int result = 0;
//	std::map<std::pair<int, int>, unsigned long long int> paths;
//
//	auto it = input.rbegin();
//	int endJoltage = *it;
//
//	for (int i = 1; i <= 3; i++)
//	{
//		result += recursionForPartTwo(input, i, 0, endJoltage, paths);
//	}
//
//
//	std::cout << "Answer for part two -> " << result << '\n';
//}
//
//unsigned long long int recursionForPartTwo(std::set<int>& input, int step, int currentJoltage, int endJoltage, std::map<std::pair<int, int>, unsigned long long int>& paths)
//{
//	unsigned long long int result = 0;
//
//	// if we already know how many ways we can get from this position to the end, we return the value
//	if (paths.find({ step + currentJoltage, endJoltage }) != paths.end())
//	{
//		return paths[{step + currentJoltage, endJoltage}];
//	}
//
//	// if not, we check if we can even stand on such a place
//	else if (input.find(currentJoltage + step) != input.end())
//	{
//		// if it turns out that from this place + our next step (1, 2, or 3 places) is the target place, we add a path
//		if (currentJoltage + step == endJoltage)
//		{
//			return 1;
//		}
//
//		// if not, we take the next possible steps from here
//		else if (currentJoltage + step < endJoltage)
//		{
//			for (int i = 1; i <= 3; i++)
//			{
//				// if we don't know how many ways we can get from the next place, we take the next step
//				if (paths.find({ i + step + currentJoltage, endJoltage }) == paths.end())
//				{
//					result += recursionForPartTwo(input, i, step + currentJoltage, endJoltage, paths);
//				}
//				else // if we know, we add the known result to the total result
//				{
//					result += paths[{ i + step + currentJoltage, endJoltage }];
//				}
//			}
//
//			// add to the map the result of how many ways we can get to a given place
//			paths.insert({ std::make_pair(step + currentJoltage, endJoltage) , result });
//		}
//	}
//
//	return result;
//}
//
//
//int main()
//{
//
//	std::set<int> joltage;
//	std::ifstream file("data.txt");
//	if (!file.is_open())
//	{
//		std::cerr << "Nie mo¿na otworzyæ pliku" << std::endl;
//		return 1;
//	}
//
//
//	std::string line;
//	while (std::getline(file, line))
//	{
//		joltage.insert(std::stoi(line));
//	}
//
//	partOne(joltage);
//	partTwo(joltage);
//
//	file.close();
//
//	return 0;
//}
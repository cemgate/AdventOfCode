//#include <iostream>
//#include <fstream>
//#include <string>
//#include <set>
//#include<vector>
//#include<sstream>
//
//
//int partOne(std::vector<std::string>& instructions);
//int partTwo(std::vector<std::string>& instructions);
//int checkForPartTwo(std::vector<std::string>& instructions);
//
//
//
//int partOne(std::vector<std::string>& instructions)
//{
//	int result = 0;
//	int i = 0;
//	std::set<int> visitedPlaces;
//
//
//	while (i < instructions.size())
//	{
//		std::istringstream iss(instructions[i]);
//		std::string ins, value;
//		iss >> ins >> value;
//
//		if (ins == "acc")
//		{
//			if (visitedPlaces.find(i) == visitedPlaces.end())
//			{
//				visitedPlaces.insert(i);
//				result += stoi(value);
//				i++;
//			}
//			else
//			{
//				break;
//			}
//		}
//		else if (ins == "jmp")
//		{
//			if (visitedPlaces.find(i) == visitedPlaces.end())
//			{
//				visitedPlaces.insert(i);
//				i += stoi(value);
//			}
//			else
//			{
//				break;
//			}
//		}
//		else
//		{
//			i++;
//		}
//	}
//	return result;
//}
//
//int partTwo(std::vector<std::string>& instructions)
//{
//	for (int i = 0; i < instructions.size(); i++)
//	{
//		std::string tmp;
//		std::istringstream iss(instructions[i]);
//		std::string ins, value;
//		iss >> ins >> value;
//
//		if (ins == "nop")
//		{
//			std::string saveForAWhile = instructions[i];
//			tmp = "jmp " + value;
//			instructions[i] = tmp;
//
//			int result = checkForPartTwo(instructions);
//
//			if (result > 0)
//			{
//				return result;
//			}
//			else
//			{
//				instructions[i] = saveForAWhile;
//			}
//		}
//		else if (ins == "jmp")
//		{
//			std::string saveForAWhile = instructions[i];
//			tmp = "nop " + value;
//			instructions[i] = tmp;
//			int result = checkForPartTwo(instructions);
//
//			if (result > 0)
//			{
//				return result;
//			}
//			else
//			{
//				instructions[i] = saveForAWhile;
//			}
//		}
//	}
//	return -1;
//}
//
//
//
//int checkForPartTwo(std::vector<std::string>& instructions)
//{
//	int result = 0;
//	int i = 0;
//	bool isBreaked = false;
//	std::set<int> visitedPlaces;
//
//
//	while (i < instructions.size())
//	{
//		std::istringstream iss(instructions[i]);
//		std::string ins, value;
//		iss >> ins >> value;
//
//		if (ins == "acc")
//		{
//			if (visitedPlaces.find(i) == visitedPlaces.end())
//			{
//				visitedPlaces.insert(i);
//				result += stoi(value);
//				i++;
//			}
//			else
//			{
//				isBreaked = true;
//				break;
//			}
//		}
//		else if (ins == "jmp")
//		{
//			if (visitedPlaces.find(i) == visitedPlaces.end())
//			{
//				visitedPlaces.insert(i);
//				i += stoi(value);
//			}
//			else
//			{
//				isBreaked = true;
//				break;
//			}
//		}
//		else
//		{
//			i++;
//		}
//	}
//
//	if (isBreaked)
//	{
//		return 0;
//	}
//
//
//	return result;
//}
//
//
//
//
//
//int main()
//{
//	std::vector<std::string> instructions;
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
//		instructions.push_back(line);
//	}
//
//	std::cout << partOne(instructions) << " part 1 answer\n";
//
//	std::cout << partTwo(instructions) << " part 2 answer\n";
//
//	file.close();
//
//
//
//	return 0;
//}
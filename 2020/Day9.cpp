#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include<vector>
#include<sstream>


bool partOne(int start, int end, unsigned long long int check, std::vector<unsigned long long int>& numbers)
{
	for (int i = start; i < end - 1; i++)
	{
		for (int j = i + 1; j < end; j++)
		{
			if (numbers[i] + numbers[j] == check)
			{
				return true;
			}
		}
	}
	return false;
}


void partTwo(unsigned long long int check, std::vector<unsigned long long int>& numbers)
{
	bool finded = false;
	int firstPlace, lastPlace;

	for (int i = 0; i < numbers.size() - 1; i++)
	{
		unsigned long long int checkValid = numbers[i];
		for (int j = i + 1; j < numbers.size(); j++)
		{
			checkValid += numbers[j];

			if (checkValid < check)
			{
				continue;
			}
			else if (checkValid > check)
			{
				break;
			}
			else
			{
				firstPlace = i;
				lastPlace = j;
				finded = true;
			}
		}
		if (finded)
		{
			std::set<unsigned long long int> resultSet;
			for (int i = firstPlace; i <= lastPlace; i++)
			{
				resultSet.insert(numbers[i]);
			}
			auto first = resultSet.begin();
			auto last = resultSet.rbegin();
			std::cout << "Answer for part two -> " << *first + (*last);
			break;
		}
	}

}
int main()
{

	std::vector<unsigned long long int> numbers;
	std::ifstream file("data.txt");
	if (!file.is_open())
	{
		std::cerr << "Cant open the file" << std::endl;
		return 1;
	}


	std::string line;
	while (std::getline(file, line))
	{
		unsigned long long int num = std::stoull(line);
		numbers.push_back(num);
	}

	for (int i = 25; i < numbers.size(); i++)
	{
		if (!partOne(i - 25, i, numbers[i], numbers))
		{
			std::cout << "Answer for part one -> " << numbers[i] << '\n';
			partTwo(numbers[i], numbers);
			break;
		}
	}

	file.close();
	return 0;
}

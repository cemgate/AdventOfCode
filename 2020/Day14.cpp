#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <sstream>
#include <map>
#include <bitset>

// Function to convert an integer to a binary string with a mask applied
std::string intToBinaryWithMask(int value, std::string mask)
{
	std::bitset<36> tmpBinary{ static_cast<unsigned long long>(value) };
	std::string binary = tmpBinary.to_string();

	// Apply the mask to the binary string
	for (int i = mask.size() - 1; i >= 0; i--)
	{
		if (mask[i] != 'X')
		{
			binary[i] = mask[i];
		}
	}
	return binary;
}

// Function to convert a binary string to an integer
unsigned long long int binaryToInt(std::string binary)
{
	unsigned long long int result = 0;
	for (int i = binary.size() - 1; i >= 0; i--)
	{
		if (binary[i] == '1')
		{
			result += std::pow(2, binary.size() - 1 - i);
		}
	}
	return result;
}

// Function to solve part one of the problem
void partOne(std::vector<std::string>& data)
{
	std::vector<std::string> masks;
	std::vector<std::vector<std::string>> masksMemorySlots;
	std::vector<std::string> tmpMemorySlots;

	// Split data into masks and corresponding memory slots
	for (auto& i : data)
	{
		size_t pos = i.find("mask");
		if (pos != std::string::npos)
		{
			if (tmpMemorySlots.size() != 0)
			{
				masksMemorySlots.push_back(tmpMemorySlots);
				tmpMemorySlots.clear();
			}
			masks.push_back(i.substr(7));
		}
		else
		{
			tmpMemorySlots.push_back(i);
		}
	}

	masksMemorySlots.push_back(tmpMemorySlots);

	unsigned long long int result = 0;
	std::map<std::string, std::string> tmpMaskMap;

	// Apply masks to the memory slots
	for (int i = 0; i < masks.size(); i++)
	{
		for (int j = 0; j < masksMemorySlots[i].size(); j++)
		{
			size_t pos = masksMemorySlots[i][j].find('=');
			if (pos != std::string::npos)
			{
				std::string mSlot = masksMemorySlots[i][j].substr(0, pos - 1);
				std::string mValue = masksMemorySlots[i][j].substr(pos + 2);

				unsigned long long number = std::stoull(mValue);
				tmpMaskMap[mSlot] = intToBinaryWithMask(number, masks[i]);
			}
		}
	}

	// Calculate the result by converting binary strings to integers
	for (auto& i : tmpMaskMap)
	{
		result += binaryToInt(i.second);
	}

	std::cout << "Answer for part one -> " << result << '\n';
}

// Function to convert an integer address to a floating address with a mask applied
std::string floatingAdres(int intAdress, std::string mask) //floating address
{
	std::bitset<36> tmpBinary{ static_cast<unsigned long long>(intAdress) };
	std::string f_adress = tmpBinary.to_string();

	// Apply the mask to the address
	for (int i = 0; i < mask.size(); i++)
	{
		if (mask[i] != '0')
		{
			f_adress[i] = mask[i];
		}
	}
	return f_adress;
}

// Function to generate all possible addresses from a floating address
void floatingNewAddresses(int startPosition, int initializeValue, std::string f_adres, std::map<unsigned long long int, unsigned long long int>& mapAdresValue)
{
	if (startPosition == f_adres.size())
	{
		unsigned long long int tmp = binaryToInt(f_adres);
		mapAdresValue[tmp] = initializeValue;
		return;
	}

	for (int i = startPosition; i < f_adres.size(); i++)
	{
		if (f_adres[i] == 'X')
		{
			f_adres[i] = '0';
			floatingNewAddresses(i + 1, initializeValue, f_adres, mapAdresValue);
			f_adres[i] = '1';
			floatingNewAddresses(i + 1, initializeValue, f_adres, mapAdresValue);
		}
	}

	unsigned long long int tmp = binaryToInt(f_adres);
	mapAdresValue[tmp] = initializeValue;
}

// Function to initialize new addresses based on a mask and address-value pair
void initalizeNewAdreses(const std::string mask, const std::string adresAndValue, std::map<unsigned long long int, unsigned long long int>& mapAdresValue)
{
	size_t start = adresAndValue.find('[') + 1;
	size_t end = adresAndValue.find(']');
	size_t eq = adresAndValue.find('=');

	int address = std::stoi(adresAndValue.substr(start, end - start));
	int initializeValue = std::stoi(adresAndValue.substr(eq + 2));

	std::string f_Adres = floatingAdres(address, mask);

	floatingNewAddresses(0, initializeValue, f_Adres, mapAdresValue);
}

// Function to solve part two of the problem
void partTwo(std::vector<std::string>& data)
{
	unsigned long long int result = 0;
	std::vector<std::string> masks;
	std::vector<std::vector<std::string>> adressesWithValues;

	std::vector<std::string> tmpMemorySlots;
	for (auto& i : data)
	{
		size_t pos = i.find("mask");

		if (pos != std::string::npos)
		{
			if (tmpMemorySlots.size() != 0)
			{
				adressesWithValues.push_back(tmpMemorySlots);
				tmpMemorySlots.clear();
			}

			masks.push_back(i.substr(7));
		}
		else
		{
			tmpMemorySlots.push_back(i);
		}
	}

	adressesWithValues.push_back(tmpMemorySlots);

	std::map<unsigned long long int, unsigned long long int> mapAdresValue;

	// Apply masks to generate all possible addresses and values
	for (int i = 0; i < masks.size(); i++)
	{
		for (int j = 0; j < adressesWithValues[i].size(); j++)
		{
			initalizeNewAdreses(masks[i], adressesWithValues[i][j], mapAdresValue);
		}
	}

	// Calculate the result by summing all values in the address map
	for (auto& i : mapAdresValue)
	{
		result += i.second;
	}

	std::cout << "Answer for part two -> " << result << '\n';
}

int main()
{
	std::vector<std::string> data;
	std::ifstream file("data.txt");

	// Check if the file is open
	if (!file.is_open())
	{
		std::cerr << "Cannot open the file" << std::endl;
		return 1;
	}

	// Read the file line by line
	std::string line;
	while (std::getline(file, line))
	{
		data.push_back(line);
	}

	// Solve part one and part two
	partOne(data);
	partTwo(data);

	file.close();

	return 0;
}

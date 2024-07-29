#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <sstream>

// Function to parse field ranges from the input data
std::vector<std::vector<int>> parseFieldRanges(std::vector<std::string>& data)
{
    std::vector<std::vector<int>> result;

    // Lambda function to parse the ranges from a given string
    auto parseRanges = [](const std::string& str) -> std::vector<int>
        {
            std::vector<int> ranges;
            std::stringstream ss(str);
            std::string part;
            char dash;

            while (ss >> part)
            {
                if (part == "or") continue;
                int start, end;
                std::stringstream rangeStream(part);
                rangeStream >> start >> dash >> end;
                ranges.push_back(start);
                ranges.push_back(end);
            }
            return ranges;
        };

    for (auto& i : data)
    {
        if (i.size() != 0)
        {
            std::size_t pos = i.find(':');
            if (pos != std::string::npos)
            {
                std::string ranges = i.substr(pos + 1);
                std::vector<int> rangeVector = parseRanges(ranges);
                result.push_back(rangeVector);
            }
        }
        else
        {
            break;
        }
    }

    return result;
}

// Function to parse the fields from the tickets
std::vector<std::vector<int>> parseTicketsFields(std::vector<std::string>& data)
{
    std::vector<std::vector<int>> result;
    bool loopControl = false;

    for (auto& i : data)
    {
        if (i == "nearby tickets:" || loopControl)
        {
            if (!loopControl)
            {
                loopControl = true;
                continue;
            }

            std::vector<int> numbers;
            std::stringstream ss(i);
            std::string item;

            while (std::getline(ss, item, ','))
            {
                numbers.push_back(std::stoi(item));
            }
            result.push_back(numbers);
        }
    }

    return result;
}

// Function to validate a single ticket based on field ranges
int isTicketValid(std::vector<std::vector<int>>& fieldsRanges, std::vector<int> ticketFields)
{
    int resultForOneTicket = 0;

    for (int i = 0; i < ticketFields.size(); i++)
    {
        bool invalidTicket = true;
        for (int j = 0; j < fieldsRanges.size(); j++)
        {
            if ((fieldsRanges[j][0] <= ticketFields[i] && ticketFields[i] <= fieldsRanges[j][1]) ||
                (fieldsRanges[j][2] <= ticketFields[i] && ticketFields[i] <= fieldsRanges[j][3]))
            {
                invalidTicket = false;
                break;
            }
        }

        if (invalidTicket)
        {
            resultForOneTicket += ticketFields[i];
        }
    }

    return resultForOneTicket;
}

// Function to handle part one of the problem
void partOne(std::vector<std::string>& data)
{
    int result = 0;
    std::vector<std::vector<int>> fieldsRanges = parseFieldRanges(data);
    std::vector<std::vector<int>> ticketsFields = parseTicketsFields(data);

    for (auto& i : ticketsFields)
    {
        int tmp = isTicketValid(fieldsRanges, i);
        if (tmp > 0)
        {
            result += tmp;
        }
    }

    std::cout << "Answer for part one -> " << result << '\n';
}

// Function to validate a single ticket for part two
int isTicketValidPartTwo(std::vector<std::vector<int>>& fieldsRanges, std::vector<int> ticketFields)
{
    for (int i = 0; i < ticketFields.size(); i++)
    {
        bool invalidTicket = true;
        for (int j = 0; j < fieldsRanges.size(); j++)
        {
            if ((fieldsRanges[j][0] <= ticketFields[i] && ticketFields[i] <= fieldsRanges[j][1]) ||
                (fieldsRanges[j][2] <= ticketFields[i] && ticketFields[i] <= fieldsRanges[j][3]))
            {
                invalidTicket = false;
                break;
            }
        }

        if (invalidTicket)
        {
            return 1;
        }
    }
    return 0;
}

// Function to transpose a 2D matrix
std::vector<std::vector<int>> transpose(const std::vector<std::vector<int>>& matrix)
{
    int rows = matrix.size();
    int cols = matrix[0].size();
    std::vector<std::vector<int>> transposed(cols, std::vector<int>(rows));

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            transposed[j][i] = matrix[i][j];
        }
    }

    return transposed;
}

// Function to check if the fields in ticketFields match the ranges in fieldsRanges
bool isThisOrignalPlaceOfField(std::vector<int>& fieldsRanges, std::vector<int>& ticketFields)
{
    for (auto& i : ticketFields)
    {
        if ((fieldsRanges[0] <= i && i <= fieldsRanges[1]) ||
            (fieldsRanges[2] <= i && i <= fieldsRanges[3]))
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}

// Function to erase invalid tickets
std::vector<std::vector<int>> eraseInvalidTickets(std::vector<std::vector<int>>& ticketsFields, std::vector<std::vector<int>>& fieldRanges)
{
    std::vector<std::vector<int>> answer;

    for (int i = 0; i < ticketsFields.size(); i++)
    {
        int result = isTicketValidPartTwo(fieldRanges, ticketsFields[i]);
        if (result == 0)
        {
            answer.push_back(ticketsFields[i]);
        }
    }
    return answer;
}

// Recursive function to erase numbers and find their original positions
void recursion(std::vector<std::set<int>>& pairs, int numberToErase, std::set<int>& erasedNumbers)
{
    for (int i = 0; i < pairs.size(); i++)
    {
        if (pairs[i].find(numberToErase) != pairs[i].end())
        {
            if (pairs[i].size() != 1)
            {
                pairs[i].erase(numberToErase);
            }
        }
    }

    erasedNumbers.insert(numberToErase);

    for (int i = 0; i < pairs.size(); i++)
    {
        if (pairs[i].size() == 1 && pairs[i].find(numberToErase) == pairs[i].end()) // Find the next number to erase
        {
            auto elementToErase = pairs[i].begin();
            int g = *elementToErase;

            if (erasedNumbers.find(*elementToErase) == erasedNumbers.end())
            {
                recursion(pairs, *elementToErase, erasedNumbers);
            }
        }
    }
}

// Function to find the real fields in part two
void findRealFields(std::vector<std::set<int>>& pairs)
{
    std::set<int> erasedNumbers;

    for (int i = 0; i < pairs.size(); i++)
    {
        if (pairs[i].size() == 1)
        {
            auto elementToErase = pairs[i].begin();
            erasedNumbers.insert(*elementToErase);
            recursion(pairs, *elementToErase, erasedNumbers);
            break;
        }
    }
}

// Function to handle part two of the problem
void partTwo(std::vector<std::string>& data)
{
    std::vector<int> ourTicket = { 107,157,197,181,71,113,179,109,97,163,73,53,101,193,173,151,167,191,127,103 };

    std::vector<std::vector<int>> fieldsRanges = parseFieldRanges(data);
    std::vector<std::vector<int>> ticketsFields = parseTicketsFields(data);

    std::vector<std::set<int>> availableFields;

    ticketsFields = eraseInvalidTickets(ticketsFields, fieldsRanges);
    ticketsFields = transpose(ticketsFields);

    for (int i = 0; i < fieldsRanges.size(); i++)
    {
        std::set<int> tmp;

        for (int j = 0; j < ticketsFields.size(); j++)
        {
            if (isThisOrignalPlaceOfField(fieldsRanges[i], ticketsFields[j]))
            {
                tmp.insert(j);
            }
        }

        availableFields.push_back(tmp);
    }

    unsigned long long int result = 1;
    findRealFields(availableFields);

    for (int i = 0; i <= 5; i++)
    {
        result *= ourTicket[*availableFields[i].begin()];
    }

    std::cout << "Answer for part two -> " << result << '\n';
}

int main()
{
    std::vector<std::string> data;
    std::ifstream file("passwords.txt");

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

    partOne(data);
    partTwo(data);

    file.close();

    return 0;
}

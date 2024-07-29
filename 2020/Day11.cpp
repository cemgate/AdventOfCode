#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <sstream>
#include <map>

namespace Moves
{
    std::pair<int, int> moveRight()
    {
        return { 0, 1 };
    }

    std::pair<int, int> moveLeft()
    {
        return { 0, -1 };
    }

    std::pair<int, int> moveUp()
    {
        return { -1, 0 };
    }

    std::pair<int, int> moveDown()
    {
        return { 1, 0 };
    }

    std::pair<int, int> moveRightUp()
    {
        return { -1, 1 };
    }

    std::pair<int, int> moveLeftUp()
    {
        return { -1, -1 };
    }

    std::pair<int, int> moveRightDown()
    {
        return { 1, 1 };
    }

    std::pair<int, int> moveLeftDown()
    {
        return { 1, -1 };
    }

    using MoveFunction = std::pair<int, int>(*)();

    const std::vector<MoveFunction> moveFunctions =
    {
        moveRight, moveLeft, moveUp, moveDown,
        moveRightUp, moveLeftUp, moveRightDown, moveLeftDown
    };
}

void changeToOccupied(std::vector<std::string>& seats)
{
    for (int i = 0; i < seats.size(); i++)
    {
        for (int j = 0; j < seats[i].size(); j++)
        {
            if (seats[i][j] == 'L')
            {
                seats[i][j] = '#';
            }
        }
    }
}

int countOccupied(std::vector < std::string>& seats)
{
    int result = 0;
    for (int i = 0; i < seats.size(); i++)
    {
        for (int j = 0; j < seats[i].size(); j++)
        {
            if (seats[i][j] == '#')
            {
                result++;
            }
        }
    }
    return result;
}

bool isOccupied(int row, int column, const std::vector<std::string>& seats)
{
    int numRows = seats.size();
    int numColumns = seats[0].size();

    return row >= 0 && row < numRows && column >= 0 && column < numColumns && seats[row][column] == '#';
}

char changeStatusOfSeatPartOne(const char seatStatus, int row, int column, const std::vector<std::string>& seats)
{
    int counterNearOccupied = 0;

    for (const auto& moveFunc : Moves::moveFunctions) // loop through all possible moves
    {
        std::pair<int, int> move = moveFunc();
        int actualRow = row + move.first;
        int actualColumn = column + move.second;

        if (isOccupied(actualRow, actualColumn, seats)) // if the place is legal and additionally occupied -> '#'
        {
            counterNearOccupied++;
            if (seatStatus == '#' && counterNearOccupied >= 4) // if there are 4 occupied seats next to us, we free the seat
            {
                return 'L';
            }
            if (seatStatus == 'L') // if the adjacent seat is occupied and our checked seat is free, we leave the seat free
            {
                return 'L';
            }
        }
    }

    if (seatStatus == 'L') // if we checked all the seats next to ours and found none occupied, we take the seat
    {
        return '#';
    }
    else if (seatStatus == '#' && counterNearOccupied < 4) // if the number of occupied seats around our checked seat is greater than 4, we free the seat
    {
        return '#';
    }

    return seatStatus;
}

char changeStatusOfSeatPartTwo(const char seatStatus, int row, int column, const std::vector<std::string>& seats)
{
    int numRows = seats.size();
    int numCols = seats[0].size();

    if (seatStatus == 'L')
    {
        for (const auto& moveFunc : Moves::moveFunctions) // loop through all possible moves
        {
            std::pair<int, int> move = moveFunc();

            int actualRow = row + move.first;
            int actualColumn = column + move.second;

            while (actualRow >= 0 && actualRow < numRows && actualColumn >= 0 && actualColumn < numCols) // check if the move is legal
            {
                if (seats[actualRow][actualColumn] == 'L') // if we see an empty seat, we move to the next move
                {
                    break;
                }
                else if (seats[actualRow][actualColumn] == '.') // if we see no seat, we look further (deeper)
                {
                    actualRow += move.first;
                    actualColumn += move.second;
                    continue;
                }
                else if (seats[actualRow][actualColumn] == '#') // if we see an occupied seat, we free the current seat
                {
                    return 'L';
                }
            }
        }

        return '#';
    }

    else if (seatStatus == '#')
    {
        int counterNearOccupied = 0;

        for (const auto& moveFunc : Moves::moveFunctions) // loop through all possible moves
        {
            std::pair<int, int> move = moveFunc();

            int actualRow = row + move.first;
            int actualColumn = column + move.second;

            while (actualRow >= 0 && actualRow < numRows && actualColumn >= 0 && actualColumn < numCols) // check if the move is legal
            {
                if (seats[actualRow][actualColumn] == 'L') // if we see an empty seat, we move to the next move
                {
                    break;
                }
                else if (seats[actualRow][actualColumn] == '.') // if we see no seat, we look further (deeper)
                {
                    actualRow += move.first;
                    actualColumn += move.second;
                    continue;
                }
                else if (seats[actualRow][actualColumn] == '#') // if we see an occupied seat, we increase the counter of occupied seats around us
                {
                    counterNearOccupied++;
                    break;
                }
            }
        }

        if (counterNearOccupied >= 5) // if the number of occupied seats around us is greater than or equal to 5, we free the seat
        {
            return 'L';
        }
    }

    return seatStatus;
}


void partOneAndTwo(std::vector<std::string>& seats, int part)
{
    changeToOccupied(seats); // change all seats to occupied

    bool seatsWasChanged = true;

    while (seatsWasChanged) // if a change occurs, the loop continues
    {
        std::vector<std::string> changedSeats; // vector to store seats after changes
        bool loopControl = false;

        for (int i = 0; i < seats.size(); i++)
        {
            std::string tmp;

            for (int j = 0; j < seats[i].size(); j++)
            {
                if (seats[i][j] == '.')
                {
                    tmp += seats[i][j]; // if the seat is the floor, just add it
                }
                else
                {
                    if (part == 1)
                    {
                        char status = changeStatusOfSeatPartOne(seats[i][j], i, j, seats); // here, a possible seat change for the first task
                        tmp += status;
                        if (status != seats[i][j]) // if a change occurred, set the flag that a change occurred
                        {
                            loopControl = true;
                        }
                    }

                    if (part == 2)
                    {
                        char status = changeStatusOfSeatPartTwo(seats[i][j], i, j, seats); // here, a possible seat change for the second task
                        tmp += status;
                        if (status != seats[i][j]) // if a change occurred, set the flag that a change occurred
                        {
                            loopControl = true;
                        }
                    }
                }
            }

            changedSeats.push_back(tmp); // add the seats to the vector
        }

        if (loopControl)
        {
            seats = changedSeats; // if a change occurred, update our vector to the new one after changes
        }
        else
        {
            seatsWasChanged = false; // if no change occurred, stop the function
        }
    }

    if (part == 1)
    {
        std::cout << "Answer for part one -> " << countOccupied(seats) << '\n';
    }
    if (part == 2)
    {
        std::cout << "Answer for part two -> " << countOccupied(seats) << '\n';
    }
}

int main()
{
    std::vector<std::string> seats;
    std::ifstream file("data.txt");

    if (!file.is_open())
    {
        std::cerr << "Cannot open the file" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line))
    {
        seats.push_back(line);
    }

    partOneAndTwo(seats, 1);
    partOneAndTwo(seats, 2);

    file.close();

    return 0;
}

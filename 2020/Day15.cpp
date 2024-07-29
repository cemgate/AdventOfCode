//#include <iostream>
//#include <unordered_map>
//
//void addToLastTimeSpokenMap(int numberToEmplace, int turn, std::unordered_map<int, std::pair<int, int>>& lastTimeSpoken)
//{
//	if (lastTimeSpoken.find(numberToEmplace) == lastTimeSpoken.end()) // if the number hasn't appeared before
//	{
//		lastTimeSpoken.emplace(std::make_pair(numberToEmplace, std::make_pair(turn, 0))); // add the number with the current turn as last spoken and 0 for previous turn (indicating it hasn't appeared before)
//	}
//	else // if the number has appeared before
//	{
//		lastTimeSpoken[numberToEmplace].second = lastTimeSpoken[numberToEmplace].first; // update the previous time it was spoken
//		lastTimeSpoken[numberToEmplace].first = turn; // update the last time it was spoken
//	}
//}
//
//void partOne(std::vector<int>& input, int turns)
//{
//	int turn = input.size() + 1;
//
//	std::unordered_map<int, std::pair<int, int>> lastTimeSpoken; // in this map, we store our numbers (keys) and the times when they were last spoken (.first) and the previous time they were spoken (.second)
//
//	for (int i = 0; i < input.size(); i++)
//	{
//		addToLastTimeSpokenMap(input[i], i + 1, lastTimeSpoken); // add the initial numbers from the input to the map
//	}
//
//	int lastNumber = input.back(); // set the last spoken number to the last number in the input
//
//	while (turn <= turns)
//	{
//		auto it = lastTimeSpoken.find(lastNumber); // look for the last spoken number
//
//		if (it != lastTimeSpoken.end())
//		{
//			if (it->second.second == 0) // if the number was spoken only once
//			{
//				addToLastTimeSpokenMap(0, turn, lastTimeSpoken); // add 0 to the map
//				lastNumber = 0; // set the last spoken number to 0
//			}
//			else // if the number was spoken more than once
//			{
//				int positionDifference = lastTimeSpoken[lastNumber].first - lastTimeSpoken[lastNumber].second; // calculate the difference between the last time it was spoken and the previous time
//				addToLastTimeSpokenMap(positionDifference, turn, lastTimeSpoken); // add the difference to the map
//				lastNumber = positionDifference; // set the last spoken number to the difference
//			}
//		}
//		turn++;
//	}
//
//	std::cout << "Answer for " << turns << " turns -> " << lastNumber << '\n';
//}
//
//int main()
//{
//	std::vector<int> input = { 1,0,15,2,10,13 };
//
//	partOne(input, 2020);
//	partOne(input, 30000000);
//
//	return 0;
//}

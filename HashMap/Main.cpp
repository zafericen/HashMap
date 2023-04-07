#include <iostream>
#include <unordered_map>
#include <cstdlib>
#include <forward_list>
#include <chrono>
#include <set>
#include <vector>
#include <bitset>

#include "LinkedMap.h"
#include "HashMap.h"

#define print(arg) std::cout<<(arg)<<std::endl;

using namespace ByteC;

class Timer
{
private:
	std::chrono::time_point<std::chrono::steady_clock> startTime;

public:
	void start()
	{
		startTime = std::chrono::high_resolution_clock::now();
	}

	double getMillis()
	{
		std::chrono::duration<double> duration = std::chrono::high_resolution_clock::now() - startTime;
		return duration.count() * 1000;
	}

	void reset()
	{
		start();
	}
};


int main()
{
	Timer timer;

	std::unordered_map<int, int,Hash<int>> table2;
	timer.start();
	for (int i{}; i < 1000000; ++i)
	{
		int random{ rand() % 10000 };
		table2[random] = i * 10;
	}
	print(timer.getMillis());

	HashMap<int, int> table;

	timer.start();
	for (int i{}; i < 1000000; ++i)
	{
		int random{ rand() % 10000 };
		table.insert(random, i * 10);
	}
	print(timer.getMillis());
	
	return 0;
}
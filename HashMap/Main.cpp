#include <iostream>
#include <unordered_map>
#include <cstdlib>
#include <forward_list>
#include <chrono>
#include <set>
#include <vector>
#include <bitset>

#include "LinkedList.h"

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

	LinkedList<size_t, int> test;
	
	timer.start();
	for (size_t i{}; i < 1000000;++i)
	{
		test.insert(std::move(i), i * 10);
	}
	print(timer.getMillis());

	for (auto& i: test)
	{
		print(test.get(i));
	}

	return 0;
}
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
	size_t sum{};

	std::forward_list<size_t> test2;

	timer.start();
	for (size_t i{}; i < 10000000; ++i)
	{
		test2.emplace_front(i);
	}
	print(timer.getMillis());

	timer.start();
	for (auto& i : test2)
	{
		sum += i;
	}
	print(timer.getMillis());
	print(sum);

	LinkedList<size_t, size_t> test;

	timer.start();
	for (size_t i{}; i < 10000000; ++i)
	{
		test.insert(std::move(i), i * 10);
	}
	print(timer.getMillis());

	timer.start();
	for (auto& i : test)
	{
		sum += i.second;
	}
	print(timer.getMillis());
	print(sum);


	return 0;
}
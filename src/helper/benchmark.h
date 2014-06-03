#pragma once
#include <string>
#include <vector>
#include <chrono>
***REMOVED***
***REMOVED***
/*
 * Benchmark execution time.
 */
class Benchmark
{
public:
	Benchmark(std::string Label);
	void Round();
	void Finish();
***REMOVED***
	static bool Output;
***REMOVED***
private:
	std::string label;
	bool active;
	std::vector<std::chrono::high_resolution_clock::time_point> starts;
};

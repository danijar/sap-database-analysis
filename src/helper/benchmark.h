#pragma once
#include <string>
#include <vector>
#include <chrono>


/*
 * Benchmark execution time.
 */
class Benchmark
{
public:
	Benchmark(std::string Label);
	void Round();
	void Finish();

	static bool Output;

private:
	std::string label;
	bool active;
	std::vector<std::chrono::high_resolution_clock::time_point> starts;
};

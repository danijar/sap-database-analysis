#pragma once
#define BENCHMARK true
#include <chrono>
#include <ctime>
#include <ratio>
***REMOVED***
// I don't exactly know why i have to do this, some problem with multiple definitions @Danijar
namespace {
***REMOVED***
// Benchmark is a static class for time measurement
struct Benchmark {
	static bool runs;
	static std::chrono::high_resolution_clock::time_point start;
***REMOVED***
	// Starts the clock if it s not already running
	static bool Start_Clock(){
		if (!runs && BENCHMARK) {
			start = std::chrono::high_resolution_clock::now();
			runs = true;
			return true;
		}
		else
			return false;
	}
***REMOVED***
	// Stops the clock and returns time duration between start and stop if clock was running
	static std::chrono::duration<double> Stop_Clock(){
		if (!runs || !BENCHMARK)
			return std::chrono::duration<double>();
		
		std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
		runs = false;
		return std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
	}
};
***REMOVED***
bool Benchmark::runs = false;
std::chrono::high_resolution_clock::time_point Benchmark::start;
***REMOVED***
}
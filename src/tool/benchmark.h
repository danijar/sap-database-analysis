#pragma once
#include <chrono>
#include <ctime>
#include <ratio>
***REMOVED***
namespace Benchmark {
	bool BENCHMARK = true;
	// Benchmark is a namespace for time measurement
	using namespace std::chrono;
***REMOVED***
	bool runs = false;
	high_resolution_clock::time_point start;
***REMOVED***
	// Starts the clock if it s not already running
	bool Start_Clock();
***REMOVED***
	// Stops the clock and returns time duration between start and stop if clock was running
	duration<double> Stop_Clock();
***REMOVED***
}
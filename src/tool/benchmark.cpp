#pragma once
#include "benchmark.h"
***REMOVED***
namespace Benchmark {
	using namespace std::chrono;
	// Starts the clock if it s not already running
	bool Start_Clock(){
		if (!runs && BENCHMARK) {
			start = high_resolution_clock::now();
			runs = true;
			return true;
		}
		else
			return false;
	}
***REMOVED***
	// Stops the clock and returns time duration between start and stop if clock was running
	duration<double> Stop_Clock(){
		if (!runs || !BENCHMARK)
			return duration<double>();
		
		high_resolution_clock::time_point end = high_resolution_clock::now();
		runs = false;
		return duration_cast<duration<double>>(end - start);
	}
***REMOVED***
}
#include "helper/benchmark.h"
#include <iostream>
#include <iomanip>
using namespace std;
using namespace std::chrono;
***REMOVED***
***REMOVED***
// Static member
bool Benchmark::Output = false;
***REMOVED***
// Constructor
Benchmark::Benchmark(string Label) : label(Label), active(true)
{
	
}
***REMOVED***
// Add another round to measure
void Benchmark::Round()
{
	// Start next round
	if (active)
		starts.push_back(high_resolution_clock::now());
}
***REMOVED***
// Redraw and add final line break
void Benchmark::Finish()
{
	if (!active)
		throw exception("Benchmark was already finished.");
	active = false;
***REMOVED***
	// Stop last round
	high_resolution_clock::time_point end = high_resolution_clock::now();
***REMOVED***
	// Calculate elapsed times
	vector<size_t> times;
	for (size_t i = 0; i < starts.size(); ++i) {
		auto from = starts[i];
		auto to = i < starts.size() - 1 ? starts[i + 1] : end;
		size_t elapsed = duration_cast<chrono::milliseconds>(to - from).count();
		times.push_back(elapsed);
	}
***REMOVED***
	// Compute average
	size_t sum = 0;
	for (auto i = times.begin(); i != times.end(); ++i)
		sum += *i;
	size_t average = sum / times.size();
***REMOVED***
	// Compute maximum
	size_t maximum = 0;
	for (auto i = times.begin(); i != times.end(); ++i)
		if (*i > maximum)
			maximum = *i;
	
	// Compute minimum
	size_t minimum = SIZE_MAX;
	for (auto i = times.begin(); i != times.end(); ++i)
		if (*i < minimum)
			minimum = *i;
***REMOVED***
	// Print results
	if (Output) {
		auto format = cout.flags();
		cout << endl;
		cout << "Benchmark" << endl << "=========" << endl
			 << "Task: " << label << endl
			 << "Rounds: " << times.size() << endl
			 << "Average: " << average << "ms" << endl
			 << "Highest: " << maximum << "ms" << endl
			 << "Lowest: " << minimum << "ms" << endl;
		cout << endl;
		cout.flags(format);
	}
}

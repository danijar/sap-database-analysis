#include <iostream>
#include <iomanip>
#include <string>
#include <unordered_set>
#include <chrono>
#include "helper/queries.h"
#include "algorithm/ratios.h"
#include "algorithm/hierarchy.h"
#include "algorithm/structures.h"
#include "tool/benchmark.h"
#include "tool/navigator.h"
#include "helper/jsonize.h"
using namespace std;
***REMOVED***
***REMOVED***
int main()
{
	// Database credentials
	Queries::Dsn = "HANA";
	Queries::User = "***REMOVED***";
	Queries::Password = "***REMOVED***";
***REMOVED***
	
	if (Benchmark::BENCHMARK) {
		Benchmark::Start_Clock();
	}
	// Fetch input
	Ratios ratios;
	
	// Take the time and print it
	if (Benchmark::BENCHMARK) {
		double duration = Benchmark::Stop_Clock().count();
		cout << "Loading the Ratios took " << std::setprecision(5) << duration << " seconds" << endl;
		Benchmark::Start_Clock();
	}
***REMOVED***
	// Build hierarchy
	Hierarchy hierarchy(ratios);
	
	// Take the time and print it
	if (Benchmark::BENCHMARK) {
		double duration = Benchmark::Stop_Clock().count();
		cout << "Loading the Hirachy took " << std::setprecision(5) << duration << " seconds" << endl;
		Benchmark::Start_Clock();
	}
***REMOVED***
	// Fetch structures
	Structures structures(ratios, hierarchy);
***REMOVED***
	// Take the time and print it
	if (Benchmark::BENCHMARK) {
		double duration = Benchmark::Stop_Clock().count();
		cout << "Loading the Structues took " << std::setprecision(5) << duration << " seconds" << endl;
	}
***REMOVED***
	// Wait for user input
	cout << "Press enter to start hierarchy navigator..." << endl;
	cout.flush();
	cin.get();
	
	// Navigate through hierarchie
	Navigator navigator(hierarchy, structures);
}

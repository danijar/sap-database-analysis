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
#include "helper/benchmark.h"
#include "helper/bar.h"
using namespace std;
***REMOVED***
***REMOVED***
int main()
{
	// Database credentials
	Queries::Dsn = "***REMOVED***";
	Queries::User = "***REMOVED***";
	Queries::Password = "***REMOVED***";
***REMOVED***
	// Compute ratio graph, hierarchy and differences
	Ratios ratios;
	Hierarchy hierarchy(ratios);
	Structures structures(ratios, hierarchy);
***REMOVED***
	/*
	// Benchmark structure generation
	Benchmark::Output = true;
	Bar::Output = false;
	cout << "Start benchmark." << endl;
	Benchmark benchmark("Overall");
	for (size_t i = 0; i < 100; ++i) {
		benchmark.Round();
		ratios.Generate();
		hierarchy.Generate();
	}
	benchmark.Finish();
	*/
***REMOVED***
	/*
	// Wait for user input
	cout << "Press enter to start hierarchy navigator..." << endl;
	cout.flush();
	cin.get();
	*/
	
	// Navigate through hierarchie
	Navigator navigator(hierarchy, structures);
}

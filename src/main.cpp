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
	double ratios_d, hirach_d, struct_d;
	ratios_d = hirach_d = struct_d = 0;
***REMOVED***
	for (int i = 0; i < 50; i++){
		if (BENCHMARK) {
			Benchmark::Start_Clock();
		}
		// Fetch input
		Ratios ratios;
***REMOVED***
		// Take the time and print it
		if (BENCHMARK) {
			double duration = Benchmark::Stop_Clock().count();
			//cout << "Loading the Ratios took " << std::setprecision(5) << duration << " seconds" << endl;
			ratios_d += duration;
			Benchmark::Start_Clock();
		}
***REMOVED***
		// Build hierarchy
		Hierarchy hierarchy(ratios);
***REMOVED***
		// Take the time and print it
		if (BENCHMARK) {
			double duration = Benchmark::Stop_Clock().count();
			//cout << "Loading the Hirachy took " << std::setprecision(5) << duration << " seconds" << endl;
			hirach_d += duration;
			Benchmark::Start_Clock();
		}
***REMOVED***
		// Fetch structures
		Structures structures(ratios, hierarchy);
***REMOVED***
		// Take the time and print it
		if (BENCHMARK) {
			double duration = Benchmark::Stop_Clock().count();
			struct_d += duration;
			//cout << "Loading the Structues took " << std::setprecision(5) << duration << " seconds" << endl;
		}
***REMOVED***
		/*structures.~Structures();
		hierarchy.~Hierarchy();
		ratios.~Ratios();*/
	}
***REMOVED***
	cout << "Loading took " << std::setprecision(5) << ratios_d/10 << "\t" << hirach_d << "\t" << struct_d << " seconds" << endl;
	// Wait for user input
	cout << "Press enter to start hierarchy navigator..." << endl;
	cout.flush();
	cin.get();
	
	// Navigate through hierarchie
	//Navigator navigator(hierarchy, structures);
}

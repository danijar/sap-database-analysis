#include <iostream>
#include <string>
#include <unordered_set>
#include "helper/queries.h"
#include "algorithm/ratios.h"
#include "algorithm/hierarchy.h"
#include "algorithm/structures.h"
#include "tool/navigator.h"
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
	// Fetch input
	Ratios ratios;
***REMOVED***
	// Build hierarchy
	Hierarchy hierarchy(ratios);
***REMOVED***
	// Fetch structures
	Structures structures(ratios, hierarchy);
***REMOVED***
	// Wait for user input
	// cout << "Press enter to start hierarchy navigator..." << endl;
	// cout.flush();
	// cin.get();
***REMOVED***
	// Navigate through hierarchie
	Navigator navigator(hierarchy, structures);
}

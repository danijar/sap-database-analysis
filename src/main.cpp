#include <iostream>
#include <string>
#include <unordered_set>
#include "algorithm/ratios.h"
#include "algorithm/hierarchy.h"
#include "algorithm/structures.h"
#include "tool/navigator.h"
#include "helper\jsonize.h"
using namespace std;
***REMOVED***
***REMOVED***
int main()
{
	// Database credentials
	string dsn = "***REMOVED***";
	string user = "***REMOVED***";
	string password = "***REMOVED***";
***REMOVED***
	// Fetch input
	Ratios ratios(dsn, user, password);
***REMOVED***
	// Build hierarchy
	Hierarchy hierarchy(ratios);
***REMOVED***
	// Fetch schemata
	// Structures schemata(ratios, dsn, user, password);
***REMOVED***
	// Wait for user input
	// cout << "Press enter to start hierarchy navigator..." << endl;
	// cout.flush();
	// cin.get();
	
	// Navigate through hierarchie
	Navigator navigator(hierarchy);
***REMOVED***
***REMOVED***
}

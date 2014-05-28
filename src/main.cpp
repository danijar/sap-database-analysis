#include <iostream>
#include <string>
#include <unordered_set>
#include "algorithm/ratios.h"
#include "algorithm/hierarchy.h"
#include "algorithm/schemata.h"
#include "tool/navigator.h"
using namespace std;
***REMOVED***
***REMOVED***
int main()
{
	// Database credentials
	string dsn = "HANA";
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
	Structures schemata(ratios, dsn, user, password);
***REMOVED***
	// Wait for user input
	cout << "Press enter to start hierarchy navigator..." << endl;
	cout.flush();
	cin.get();
***REMOVED***
	// Navigate through hierarchie
	Navigator navigator(hierarchy);
}

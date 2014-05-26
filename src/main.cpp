#include <iostream>
#include <unordered_set>
#include "algorithm/input.h"
#include "algorithm/hierarchy.h"
#include "algorithm/schemata.h"
#include "tool/navigator.h"
using namespace std;
***REMOVED***
***REMOVED***
int main()
{
	// Fetch input
	Input input("HANA", "***REMOVED***", "***REMOVED***");
	
	// Fetch schemata
	Schemata schemata(input, "HANA", "***REMOVED***", "***REMOVED***");
***REMOVED***
	// Build hierarchy
	Hierarchy hierarchy(input);
***REMOVED***
	// Wait for user input
	cout << "Press enter to start hierarchy navigator..." << endl;
	cin.get();
***REMOVED***
	// Navigate through hierarchie
	Navigator navigator(hierarchy);
}

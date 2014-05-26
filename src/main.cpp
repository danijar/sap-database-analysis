#include "input.h"
#include <iostream>
#include <unordered_set>
#include "navigator.h"
#include "schemata.h"
using namespace std;
***REMOVED***
***REMOVED***
int main()
{
	Input input("HANA", "***REMOVED***", "***REMOVED***");
	// For testing
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

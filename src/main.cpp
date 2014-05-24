#include "input.h"
#include <iostream>
#include <unordered_set>
#include "navigator.h"
using namespace std;
***REMOVED***
int main()
{
	// Load input data from database or dump
	Input input;
	if (input.Saved())
		input.Load();
	else {
		input.Fetch("***REMOVED***", "***REMOVED***", "***REMOVED***");
		if (input.ids.size())
			input.Save();
	}
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

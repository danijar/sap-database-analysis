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
		input.Fetch("HANA", "***REMOVED***", "***REMOVED***", true);
		if (input.ids.size())
			input.Save();
	}
***REMOVED***
	// Initialize set with all parents
	unordered_set<size_t> heads;
	heads.reserve(input.ratios.size());
	for (auto i = input.ratios.begin(); i != input.ratios.end(); ++i)
		heads.insert(i->first);
	cout << "Filled with " << input.ratios.size() << " ids." << endl;
***REMOVED***
	// Remove tables that have parents
	for (auto i = input.ratios.begin(); i != input.ratios.end(); ++i) {
		for (auto j = i->second.begin(); j != i->second.end(); ++j) {
			auto k = heads.find(j->first);
			if (k != heads.end())
				heads.erase(k);
		}
	}
	
	// Navigate through hierarchie
	Navigator navigator(input, heads);
***REMOVED***
	// Hold console open
	cin.get();
	cin.get();
}

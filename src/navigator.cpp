#include "navigator.h"
#include <iostream>
#include "queries.h"
using namespace std;
***REMOVED***
// Constructor
Navigator::Navigator(Input &Input, unordered_set<size_t> &Heads) : input(Input), heads(Heads)
{
	for (;;) {
		// List current level
		cout << endl;
		List();
		cout << endl;
***REMOVED***
		// Navigation
		cout << "Navigate to: ";
		string name;
		cin >> name;
***REMOVED***
		// One table up
		if (name == "..") {
			Up();
		}
***REMOVED***
		// Root level
		else if (name == "/") {
			path.clear();
		}
***REMOVED***
		// List scheme
		else if (name == "ls") {
			if (path.size()) {
				vector<string> fields = Queries::Schema(input.names[path.back()]);
				for (auto i : fields)
					cout << i << " ";
				cout << endl;
			}
		}
***REMOVED***
		// Specified table
		else {
			Go(name);
		}
	}
}
***REMOVED***
// Go down one level in the hierarchie
bool Navigator::Go(string Name)
{
	// Find node navigating to
	auto i = input.ids.find(Name);
	
	// Name doesn't match
	if (i == input.ids.end())
		return false;
***REMOVED***
	// Add to path
	path.push_back(i->second);
	return true;
}
***REMOVED***
// Get one level up in the hierarchie
bool Navigator::Up()
{
	// If already on the highest level
	if (!path.size())
		return false;
***REMOVED***
	// Remove last from path
	size_t node = path.back();
	path.pop_back();
	return true;
}
***REMOVED***
// List children of current table
void Navigator::List()
{
	// On highest level
	if (!path.size()) {
		// Super parents
		cout << "Heads" << endl << "-----" << endl;
		cout << "Found " << heads.size() << " heads." << endl;
		int counter = 0;
		const int limit = 20;
		for (auto i = heads.begin(); i != heads.end() && counter < limit; ++i, ++counter) {
			cout << input.names[*i] << " (" << Children(*i) << ")" << endl;
		}
		if (heads.size() > limit)
			cout << "..." << endl;
	}
***REMOVED***
	// Current node name
	else {
		size_t id = path.back();
		string name = input.names[id];
		cout << name << endl;
		for (size_t i = 0; i < name.length(); ++i)
			cout << "-";
		cout << endl;
***REMOVED***
		// Children's names
		if (input.ratios.find(id) == input.ratios.end()) {
			cout << "Found no children." << endl;
		} else {
			cout << "Found " << input.ratios[id].size() << " children." << endl;
			int counter = 0;
			const int limit = 20;
			for (auto i = input.ratios[id].begin(); i != input.ratios[id].end() && counter < limit; ++i, ++counter) {
				cout << input.names[i->first] << " (" << Children(i->first) << ")" << endl;
			}
			if (input.ratios[id].size() > limit)
				cout << "..." << endl;
		}
	}
}
***REMOVED***
// Get number of children of a table
size_t Navigator::Children(size_t Id)
{
	// No children
	if (input.ratios.find(Id) == input.ratios.end())
		return 0;
***REMOVED***
	// Get number of children
	return input.ratios[Id].size();
}

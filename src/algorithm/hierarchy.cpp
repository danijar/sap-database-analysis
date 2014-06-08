#include "algorithm/hierarchy.h"
#include <iostream>
#include "helper/serialize.h"
using namespace std;
***REMOVED***
***REMOVED***
// Constructor
Hierarchy::Hierarchy(Ratios &Ratios, string Path) : ids(Ratios.ids), names(Ratios.names), ratios(Ratios.ratios)
{
	// Try to load dump
	if (Load(Path)) {
		cout << "Loaded cached hierarchy." << endl;
		return;
	}
***REMOVED***
	Generate();
	if (ids.size())
		Save(Path);
}
***REMOVED***
// Reset and load data from disk
bool Hierarchy::Load(string Path)
{
	if (!Saved())
		return false;
***REMOVED***
	// Reset data
	children.clear();
***REMOVED***
	// Initialize stream
	Deserialize in(Path);
	if (!in.Good())
		return false;
***REMOVED***
	// Read data
	in >> children;
	in >> amounts;
***REMOVED***
	return true;
}
***REMOVED***
// Save current data to disk
bool Hierarchy::Save(string Path)
{
	// Initialize stream
	Serialize out(Path);
	if (!out.Good())
		return false;
***REMOVED***
	// Write data
	out << children;
	out << amounts;
***REMOVED***
	return true;
}
***REMOVED***
// Check whether there is a dump file at this location
bool Hierarchy::Saved(string Path)
{
	ifstream stream(Path.c_str());
	bool result = stream.good();
	stream.close();
	return result;
}
***REMOVED***
// Find head tables
unordered_set<size_t> Hierarchy::Heads()
{
	// Initialize set with all parents except root
	unordered_set<size_t> heads;
	heads.reserve(ratios.size() - 1);
	for (size_t i = 1; i < ratios.size(); ++i)
		heads.insert(heads.end(), i);
***REMOVED***
	// Remove tables that have parents
	Bar bar("Find head tables", ratios.size());
	for (auto i = ratios.begin(); i != ratios.end(); ++i) {
		for (auto j = i->begin(); j != i->end(); ++j)
			heads.erase(j->first);
		bar.Increment();
	}
	bar.Finish();
***REMOVED***
	// Remove tables that have no children
	auto iterator = heads.begin();
	while (iterator != heads.end()) {
		auto i = iterator++;
		if (*i > children.size() - 1 || !children[*i].size())
			heads.erase(i);
	}
***REMOVED***
	return heads;
}
***REMOVED***
void Hierarchy::Generate()
{
	// Add children of all nodes to hierarchy
	Bar bar("Build hierarchy", ids.size());
	processed.clear();
	children.clear();
	children.resize(names.size());
	for (size_t i = 1; i < names.size(); ++i) {
		Children(i);
		bar.Increment();
	}
	bar.Finish();
***REMOVED***
	// Attach head tables to root node
	auto heads = Heads();
	for (auto i = heads.begin(); i != heads.end(); ++i)
		children[0].insert(*i);
***REMOVED***
	// Calculate recursive amount of children starting at root
	amounts.clear();
	amounts.resize(names.size());
	Bar amount_bar("Calculate depth", names.size());
	Amount(0, &amount_bar);
	amount_bar.Finish();
}
***REMOVED***
// Return list of all tables under the specified one
unordered_set<size_t> Hierarchy::Subchildren(size_t Root)
{
	unordered_set<size_t> result;
***REMOVED***
	// Iterate over direct children
	for (auto i = children[Root].begin(); i != children[Root].end(); ++i) {
		// Add direct children itself
		result.insert(*i);
***REMOVED***
		// Recusrively add next levels
		auto current = Subchildren(*i);
		result.insert(current.begin(), current.end());
	}
	
	return result;
}
***REMOVED***
// Add children of given table to hierarchy
void Hierarchy::Children(size_t Id)
{
	// Skip if there are no children
	if (Id > ratios.size() - 1)
		return;
***REMOVED***
	// Process children
	for (auto i = ratios[Id].begin(); i != ratios[Id].end(); ++i) {
		size_t child = i->first;
		
		// Don't assign children more than once
		if (processed.find(child) != processed.end())
			continue;
		processed.insert(child);
***REMOVED***
		// Start with actual parent based on input data
		size_t parent = Id;
		float ratio = i->second;
***REMOVED***
		// Try to find stronger match among siblings
		for (auto j = ratios[Id].begin(); j != ratios[Id].end(); ++j) {
			size_t current = j->first;
***REMOVED***
			// Check for connection to current table
			if (ratios[current].find(child) == ratios[current].end())
				continue;
			
			// Update parent if better match
			if (ratios[current][child] > ratio) {
				parent = current;
				ratio = ratios[current][child];
			}
		}
***REMOVED***
		// Add to tree
		children[parent].insert(child);
	}
}
***REMOVED***
// Calculate recursive amount of children
size_t Hierarchy::Amount(size_t Id, Bar *Bar)
{
	// Calculate amount if not cached
	if (!amounts[Id]) {
		size_t sum = children[Id].size();
		for (auto i = children[Id].begin(); i != children[Id].end(); ++i)
			sum += Amount(*i, Bar);
		amounts[Id] = sum;
		Bar->Increment();
	}
	
	return amounts[Id];
}

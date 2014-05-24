#include "hierarchy.h"
#include <iostream>
#include "bar.h"
using namespace std;
***REMOVED***
***REMOVED***
// Constructor
Hierarchy::Hierarchy(Input &Input) : ids(Input.ids), names(Input.names), ratios(Input.ratios)
{
	// Add children of all nodes to hierarchy
	Bar bar("Build hierarchy", ids.size());
	for (auto i = ids.begin(); i != ids.end(); ++i) {
		Children(i->second);
		bar.Increment();
	}
	bar.Finish();
***REMOVED***
	// Attach head tables to root node
	auto heads = Heads(Input);
	for (auto i = heads.begin(); i != heads.end(); ++i)
		children[0].insert(*i);
}
***REMOVED***
unordered_set<size_t> Hierarchy::Heads(Input &Input)
{
	// Initialize set with all parents
	unordered_set<size_t> heads;
	heads.reserve(ratios.size());
	for (auto i = ratios.begin(); i != ratios.end(); ++i)
		heads.insert(i->first);
***REMOVED***
	// Remove tables that have parents
	Bar bar("Find head tables", ratios.size());
	for (auto i = ratios.begin(); i != ratios.end(); ++i) {
		for (auto j = i->second.begin(); j != i->second.end(); ++j)
			heads.erase(j->first);
		bar.Increment();
	}
	bar.Finish();
***REMOVED***
	// Remove tables that have no children
	auto iterator = heads.begin();
	while (iterator != heads.end()) {
		auto i = iterator++;
		if (children.find(*i) == children.end() || !children[*i].size())
			heads.erase(i);
	}
	
	return heads;
}
***REMOVED***
// Add children of given table to hierarchy
void Hierarchy::Children(size_t Id)
{
	// Skip if there are no children
	if (ratios.find(Id) == ratios.end())
		return;
***REMOVED***
	// Process children
	for (auto i = ratios[Id].begin(); i != ratios[Id].end(); ++i) {
		size_t child = i->first;
***REMOVED***
		// Start with actual parent based on input data
		size_t parent = Id;
		float ratio = i->second;
***REMOVED***
		// Try to find stronger match among siblings
		for (auto j = ratios[Id].begin(); j != ratios[Id].end(); ++j) {
			size_t current = j->first;
***REMOVED***
			// Skip if there are no children
			if (ratios.find(current) == ratios.end())
				continue;
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
		if (processed.find(child) == processed.end()) {
			children[parent].insert(child);
			processed.insert(child);
		}
	}
}

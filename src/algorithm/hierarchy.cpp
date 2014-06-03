#include "algorithm/hierarchy.h"
#include <iostream>
#include "helper/serialize.h"
using namespace std;
***REMOVED***
***REMOVED***
// Constructor
Hierarchy::Hierarchy(Ratios &Ratios, string Path) : ratios(Ratios.ratios)
{
	// Try to load dump
	if (Saved(Path) && Load(Path)) {
		cout << "Loaded cached hierarchy." << endl;
		return;
	}
***REMOVED***
	Generate();
	if (children.size())
		Save(Path);
}
***REMOVED***
// Reset and load data from disk
bool Hierarchy::Load(string Path)
{
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
	in >> names;
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
	out << names;
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
unordered_set<string> Hierarchy::Heads()
{
	// Initialize set with all parents except root
	unordered_set<string> heads;
	heads.reserve(names.size() - 1);
	//for (size_t i = 1; i < ratios.size(); ++i)
	//	heads.insert(heads.end(), i);
	for (auto i = names.begin(); i != names.end(); i++){
		heads.insert(*i);
	}
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
		if (!children[*i].size())
			heads.erase(i);
	}
***REMOVED***
	return heads;
}
***REMOVED***
void Hierarchy::Generate()
{
	// Add children of all nodes to hierarchy
	Bar bar("Build hierarchy", ratios.size());
	processed.clear();
	children.clear();
	names.clear();
	
	for (auto i = ratios.begin(); i != ratios.end(); ++i) 
		if (names.find(i->first) == names.end())
			names.insert(i->first);
	
	children.reserve(names.size());
	for (auto i = names.begin(); i != names.end(); ++i) {
		Children(*i);
		bar.Increment();
	}
	bar.Finish();
***REMOVED***
	// Attach head tables to root node
	auto heads = Heads();
	
	children.insert(make_pair(string("<root>"), unordered_set<string>()) );
***REMOVED***
	for (auto i = heads.begin(); i != heads.end(); ++i)
		children[string("<root>")].insert(*i);
***REMOVED***
	// Calculate recursive amount of children starting at root
	amounts.clear();
	Bar amount_bar("Calculate depth", ratios.size());
	Amount(children.begin()->first, &amount_bar);
	amount_bar.Finish();
}
***REMOVED***
// Add children of given table to hierarchy
void Hierarchy::Children(string Id)
{
	// Skip if there are no children
	if (names.find(Id) == names.end())
		return;
***REMOVED***
	// Process children
	for (auto i = ratios[Id].begin(); i != ratios[Id].end(); ++i) {
		string child = i->first;
		
		// Don't assign children more than once
		if (processed.find(child) != processed.end())
			continue;
		processed.insert(child);
***REMOVED***
		// Start with actual parent based on input data
		string parent = Id;
		float ratio = i->second;
***REMOVED***
		// Try to find stronger match among siblings
		for (auto j = ratios[Id].begin(); j != ratios[Id].end(); ++j) {
			string current = j->first;
***REMOVED***
			// Check for connection to current table
			if (ratios[current].find(child) == ratios[current].end())
				continue;
			
			// Update parent if better match
			if (ratios[current][child] > ratio) {
				parent = current;
				ratio = ratios[parent][child];
			}
		}
***REMOVED***
		// Add to tree
		/*
		if (children.find(parent) == children.end())
			children.insert(make_pair(parent, unordered_set<string>()));
		*/
		children[parent].insert(child);
	}
}
***REMOVED***
// Calculate recursive amount of children
size_t Hierarchy::Amount(string Id, Bar *Bar)
{
	// Calculate amount if not cached
	if (amounts.find(Id) == amounts.end()) {
		size_t sum = children[Id].size();
		//int test = 0;
		//cout << children[Id].size() << " ";
		for (auto i = children[Id].begin(); i != children[Id].end(); ++i) {
		//	test++;
		//	cout << ".";
			sum += Amount(*i, Bar);
		}
	//	cout << endl;
		amounts.insert(make_pair(Id, sum));
		//amounts[Id] = sum;
		Bar->Increment();
	}
	
	return amounts[Id];
}

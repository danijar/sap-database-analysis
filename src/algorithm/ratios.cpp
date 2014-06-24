#include "algorithm/ratios.h"
#include <iostream>
#define OTL_ODBC
#define OTL_STL
#include "otlv4.h"
#include "helper/bar.h"
#include "helper/serialize.h"
using namespace std;
***REMOVED***
***REMOVED***
// Constructor checks for dump or queries
Ratios::Ratios(string Path)
{
	// Try to load dump
	if (Load(Path)) {
		cout << "Loaded cached ratios." << endl;
		return;
	}
***REMOVED***
	Fetch();
	if (ids.size())
		Save(Path);
}
***REMOVED***
// Fetch input from database and generate graph from it
void Ratios::Fetch(bool Output)
{
	// Reset data
	ids.clear();
	names.clear();
	ratios.clear();
***REMOVED***
	// Query rows from database
	rows = Queries::Ratios();
	Generate();
***REMOVED***
	// Output
	if (Output) {
		// Count connections
		size_t connections = 0;
		for (auto i = ratios.begin(); i != ratios.end(); ++i)
			connections += i->size();
***REMOVED***
		// Print message
		cout << fixed;
		cout << "Loaded "
			 << ids.size() << " tables and "
			 << connections << " connections stored in "
			 << 0.001 * (1000 * Size() / 1024 / 1024) << " megabytes of memory."
			 << endl;
		cout << scientific;
	}
}
***REMOVED***
// Reset and load data from disk
bool Ratios::Load(string Path)
{
	if (!Saved())
		return false;
***REMOVED***
	// Reset data
	rows.clear();
	ids.clear();
	names.clear();
	ratios.clear();
	
	// Initialize stream
	Deserialize in(Path);
	if (!in.Good())
		return false;
***REMOVED***
	// Read data
	in >> rows;
	in >> ids;
	in >> names;
	in >> ratios;
***REMOVED***
	return true;
}
***REMOVED***
// Save current data to disk
bool Ratios::Save(string Path)
{
	// Initialize stream
	Serialize out(Path);
	if (!out.Good())
		return false;
***REMOVED***
	// Write data
	out << rows;
	out << ids;
	out << names;
	out << ratios;
***REMOVED***
	return true;
}
***REMOVED***
// Check whether there is a dump file at this location
bool Ratios::Saved(string Path)
{
	ifstream stream(Path.c_str());
	bool result = stream.good();
	stream.close();
	return result;
}
***REMOVED***
// Build ratio graph
void Ratios::Generate()
{
	// Skip if empty
	if (!rows.size()) {
		cout << "No rows to process." << endl;
		return;
	}
***REMOVED***
	// Clear data
	names.clear();
	ids.clear();
	ratios.clear();
***REMOVED***
	// Push root node at index zero
	names.push_back({"<root>"});
	ids.insert(make_pair("<root>", 0));
	ratios.emplace_back();
***REMOVED***
	// Fetch distinct table names
	Bar bar("Unpack data", rows.size() * 2);
***REMOVED***
	for (auto i = rows.begin(); i != rows.end(); ++i) {
		// Get or generate parent id		
		size_t parent_id = Id(i->parent);
***REMOVED***
		// Don't add if child and parent are the same
		if (i->parentratio >= 1.0f && i->childratio >= 1.0f) {
			// Add to the mapping of names and id
			names[parent_id].insert(i->child);
			ids[i->child] = parent_id;
			continue;
		}
		
		// Create node for child
		Id(i->child);
		bar.Increment();
	}
***REMOVED***
	// Create graph from query rows
	ratios.resize(names.size());
	for (auto i = rows.begin(); i != rows.end(); ++i) {
		// Get table ids from row
		size_t parent = ids[i->parent];
		size_t child = ids[i->child];
		
		// Do not add ratio for copies
		if (parent == child) continue;
	
		if (parent > ratios.size() - 1)
			cout << endl << parent << endl << ratios.size();
***REMOVED***
		// Add parent ratio
		ratios[parent][child] = i->parentratio;
		
		bar.Increment();
	}
	bar.Finish();
}
***REMOVED***
// Get or create id of a table name
size_t Ratios::Id(string name)
{
	// Add if not already in map
	auto i = ids.find(name);
	if (i == ids.end()) {
		size_t counter = 0;
		// Check in all names if we already have an id 
		for (auto j = names.begin(); j != names.end(); j++, counter++)
			if (j->find(name) != j->end())
				return counter;
***REMOVED***
		size_t id = names.size();
		names.push_back({ name });
		ids[name] = id;
		return id;
	}
***REMOVED***
	// Otherwise return existing
	else
		return i->second;
}
***REMOVED***
// Calculate memory size in bytes
size_t Ratios::Size()
{
	size_t size = 0;
***REMOVED***
	// Dictionary encoded names
	for (auto i = ids.begin(); i != ids.end(); ++i)
		size += i->first.length() + sizeof(size_t);
***REMOVED***
	// Ratios
	size += ratios.size() * sizeof(size_t);
	for (auto i = ratios.begin(); i != ratios.end(); ++i)
		size += i->size() * (sizeof(size_t) + sizeof(float));
***REMOVED***
	return size;
}

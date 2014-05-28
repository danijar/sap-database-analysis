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
	if (Saved(Path) && Load(Path)) {
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
	auto rows = Queries::Ratios();
	Graph(rows);
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
	// Reset data
	ids.clear();
	names.clear();
	ratios.clear();
	
	// Initialize stream
	Deserialize in(Path);
	if (!in.Good())
		return false;
***REMOVED***
	// Read data
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
// Get or create id of a table name
size_t Ratios::Id(string name)
{
	// Add if not already in map
	auto i = ids.find(name);
	if (i == ids.end()) {
		size_t id = names.size();
		names.push_back(name);
		ids[name] = id;
		return id;
	}
***REMOVED***
	// Otherwise return existing
	else
		return i->second;
}
***REMOVED***
// Build ratio graph
void Ratios::Graph(vector<Queries::Ratio> &Rows)
{
	// Skip if empty
	if (!Rows.size()) {
		cout << "No rows to process." << endl;
		return;
	}
***REMOVED***
	// Push root node at index zero
	names.push_back("<root>");
	ids.insert(make_pair("<root>", 0));
	ratios.emplace_back();
***REMOVED***
	// Fetch distinct table names
	Bar bar("Unpack data", Rows.size() * 2);
	for (auto i = Rows.begin(); i != Rows.end(); ++i) {
		// Create nodes
		Id(i->parent);
		Id(i->child);
***REMOVED***
		bar.Increment();
	}
***REMOVED***
	// Create graph from query rows
	ratios.resize(names.size());
	for (auto i = Rows.begin(); i != Rows.end(); ++i) {
		// Get table ids from row
		size_t parent = ids[i->parent];
		size_t child = ids[i->child];
***REMOVED***
		if (parent > ratios.size() - 1)
			cout << endl << parent << endl << ratios.size();
***REMOVED***
		// Add parent ratio
		ratios[parent][child] = i->parentratio;
		
		// For now, ignore child ratio completely
		// Ratio(child, parent, i->childratio);
***REMOVED***
		bar.Increment();
	}
	bar.Finish();
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

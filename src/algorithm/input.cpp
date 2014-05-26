#include "algorithm/input.h"
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
Input::Input(string Dsn, string User, string Password, string Path)
{
	// Try to load dump
	if (Saved(Path) && Load(Path)) {
		cout << "Loaded cached ratios." << endl;
		return;
	}
***REMOVED***
	Fetch(Dsn, User, Password);
	if (ids.size())
		Save(Path);
}
***REMOVED***
// Fetch input from database and generate graph from it
void Input::Fetch(string Dsn, string User, string Password, bool Output)
{
	// Reset data
	ids.clear();
	names.clear();
	ratios.clear();
***REMOVED***
	// Query rows from database
	auto rows = Queries::Ratios(Dsn, User, Password);
	Graph(rows);
***REMOVED***
	// Output
	if (Output) {
		// Count connections
		size_t connections = 0;
		for (auto i = ratios.begin(); i != ratios.end(); ++i)
			connections += i->second.size();
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
bool Input::Load(string Path)
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
bool Input::Save(string Path)
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
bool Input::Saved(string Path)
{
	ifstream stream(Path.c_str());
	bool result = stream.good();
	stream.close();
	return result;
}
***REMOVED***
// Get or create id of a table name
size_t Input::Id(string name)
{
	// Add if not already in map
	auto i = ids.find(name);
	if (i == ids.end()) {
		size_t id = ids.size() + 1;
		ids[name] = id;
		names[id] = name;
		return id;
	}
***REMOVED***
	// Otherwise return existing
	else
		return i->second;
}
***REMOVED***
// Build ratio graph
void Input::Graph(vector<Queries::ratio_row> &Rows)
{
	// Skip if empty
	if (!Rows.size()) {
		cout << "No rows to process." << endl;
		return;
	}
***REMOVED***
	// Create graph from query rows
	Bar bar("Unpack data", Rows.size());
	for (auto i = Rows.begin(); i != Rows.end(); ++i) {
		// Create nodes
		size_t parent = Id(i->parent);
		size_t child = Id(i->child);
***REMOVED***
		// Create edges
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
size_t Input::Size()
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
		size += i->second.size() * (sizeof(size_t) + sizeof(float));
***REMOVED***
	return size;
}

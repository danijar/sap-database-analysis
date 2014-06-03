#include "algorithm/structures.h"
#include "helper/queries.h"
#include "helper/serialize.h"
using namespace std;
***REMOVED***
***REMOVED***
// Constructor checks dump and fetch data
Structures::Structures(Ratios &Ratios, Hierarchy &Hierarchy, string Path) : hierarchy(Hierarchy), names(Hierarchy.names)
{
	// Try to load dump
	if (Saved(Path) && Load(Path)) {
		cout << "Loaded cached schemata." << endl;
		return;
	}
***REMOVED***
	Fetch();
	Generate();
	if (structures.size())
		Save(Path);
}
***REMOVED***
// Fetch fields from database and build map from it
void Structures::Fetch(bool Output)
{
	// Reset data
	structures.clear();
	differences.clear();
***REMOVED***
	// Fetch schemata from database
	
	structures = Queries::Structures(names);
***REMOVED***
	// Output
	if (Output) {
		// Count connections
		size_t fields = 0;
		for (auto i = structures.begin(); i != structures.end(); ++i)
			fields += i->second.size();
***REMOVED***
		// Print message
		cout << fixed;
		cout << "Loaded "
			<< fields << " fields stored in "
			<< 0.001 * (1000 * Size() / 1024 / 1024) << " megabytes of memory."
			<< endl;
		cout << scientific;
	}
}
***REMOVED***
// Reset and load data from disk
bool Structures::Load(string Path)
{
	// Reset data
	structures.clear();
	differences.clear();
	names.clear();
	// Initialize stream
	Deserialize in(Path);
	if (!in.Good())
		return false;
***REMOVED***
	// Read data
	in >> structures;
	in >> differences;
	in >> names;
	return true;
}
***REMOVED***
// Save current data to disk
bool Structures::Save(string Path)
{
	// Initialize stream
	Serialize out(Path);
	if (!out.Good())
		return false;
***REMOVED***
	// Structures
	out << structures;
	out << differences;
	out << names;
	return true;
}
***REMOVED***
// Check whether there is a dump file at this location
bool Structures::Saved(string Path)
{
	ifstream stream(Path.c_str());
	bool result = stream.good();
	stream.close();
	return result;
}
***REMOVED***
// Compute added and removed fields between any two tables
pair<unordered_set<string>, unordered_set<string>> Structures::Difference(string Parent, string Child)
{
	pair<unordered_set<string>, unordered_set<string>> result;
	
	// Find added fields
	for (auto i = structures[Child].begin(); i != structures[Child].end(); ++i) {
		// Using the own find operator because find doesent use def. comperator
		if (std::find_if(structures[Parent].begin(), structures[Parent].end(),
				Queries::find_field(*i)) == structures[Parent].end())
			result.first.insert(i->name);
	}
***REMOVED***
	// Find removed streams
	for (auto i = structures[Parent].begin(); i != structures[Parent].end(); ++i) {
		// Using the own find operator because find doesent use def. comperator
		if (std::find_if(structures[Child].begin(), structures[Child].end(),
			Queries::find_field(*i)) == structures[Child].end())
			result.second.insert(i->name);
	}
***REMOVED***
	return result;
}
***REMOVED***
// Return cached difference for a child to its parent
pair<unordered_set<string>, unordered_set<string>> &Structures::Difference(string Child)
{
	// Check for valid table
	if (differences.find(Child) == differences.end())
		throw exception("Table index out of range");
***REMOVED***
	return differences[Child];
}
***REMOVED***
// Batch compute differences from all tables to their parents
void Structures::Generate()
{
	// Initialize container
	differences.reserve(names.size());
***REMOVED***
	// Compute for each children of current table
	for (auto i = names.begin(); i != names.end(); ++i)
		for (auto j = hierarchy.children[*i].begin(); j != hierarchy.children[*i].end(); ++j)
				differences[*j] = Difference(*i, *j);
}
***REMOVED***
// Calculate memory size in bytes
size_t Structures::Size()
{
	size_t size = 0;
***REMOVED***
	// Structures
	size += structures.size() * sizeof(string);
	for (auto i = structures.begin(); i != structures.end(); ++i)
		size += i->second.size() * (sizeof(string)+sizeof(Queries::Field));
***REMOVED***
	// Differences
	// ...
***REMOVED***
	return size;
}

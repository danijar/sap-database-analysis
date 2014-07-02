#include "algorithm/structures.h"
#include "helper/queries.h"
#include "helper/serialize.h"
using namespace std;
***REMOVED***
***REMOVED***
// Constructor checks dump and fetch data
Structures::Structures(Ratios &Ratios, Hierarchy &Hierarchy, string Path) : ids(Ratios.ids), hierarchy(Hierarchy)
{
	// Try to load dump
	if (Load(Path)) {
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
	categories.clear();
	
	// Fetch schemata from database
	structures = Queries::Structures(ids);
***REMOVED***
	// Output
	if (Output) {
		// Count connections
		size_t fields = 0;
		for (auto i = structures.begin(); i != structures.end(); ++i)
			fields += i->size();
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
	if (!Saved())
		return false;
***REMOVED***
	// Reset data
	structures.clear();
	differences.clear();
	categories.clear();
***REMOVED***
	// Initialize stream
	Deserialize in(Path);
	if (!in.Good())
		return false;
***REMOVED***
	// Read data
	in >> structures;
	in >> differences;
	in >> categories;
***REMOVED***
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
	out << categories;
***REMOVED***
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
// Batch compute differences from all tables to their parents
void Structures::Generate()
{
	// Initialize container
	differences.resize(hierarchy.names.size());
	categories.resize(hierarchy.names.size());
***REMOVED***
	// Compute for each children of current table
	for (size_t i = 0; i < hierarchy.names.size(); ++i) 
		for (auto j = hierarchy.children[i].begin(); j != hierarchy.children[i].end(); ++j) {
			pair<unordered_set<string>, unordered_set<string>> difference = Difference(i, *j);
			differences[*j] = difference;
			categories[*j] = categorize(difference, i, *j);
		}
}
***REMOVED***
// Compute added and removed fields between any two tables
pair<unordered_set<string>, unordered_set<string>> Structures::Difference(size_t Parent, size_t Child)
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
	
	return result;
}
***REMOVED***
size_t Structures::categorize(pair<unordered_set<string>, unordered_set<string>> difference, size_t parent, size_t child) {
	size_t category = 0;
	// Categories the relationship
***REMOVED***
	// If only added add 1000 to the categorie
	if (difference.second.size() == 0)
		category += 1000;
	// Calculate a percentage value for how many fields have changed
	if ((difference.first.size() + difference.second.size()) > 0)
		category += (size_t)(100 * ((float)structures.at(child).size()) / (difference.first.size() + difference.second.size()));
***REMOVED***
	return category;
}
***REMOVED***
// Return cached difference for a child to its parent
pair<unordered_set<string>, unordered_set<string>> &Structures::Difference(size_t Child)
{
	// Check for valid table
	if (Child > differences.size() - 1)
		throw exception("Table index out of range");
***REMOVED***
	return differences[Child];
}
***REMOVED***
// Calculate memory size in bytes
size_t Structures::Size()
{
	size_t size = 0;
***REMOVED***
	// Structures
	size += structures.size() * sizeof(size_t);
	for (auto i = structures.begin(); i != structures.end(); ++i)
		size += i->size() * (sizeof(size_t)+sizeof(Queries::Field));
***REMOVED***
	// Differences
	// ...
***REMOVED***
	return size;
}

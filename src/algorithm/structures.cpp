#include "algorithm/structures.h"
#include "helper/queries.h"
#include "helper/serialize.h"
using namespace std;
***REMOVED***
***REMOVED***
// Constructor checks dump and fetch data
Structures::Structures(Ratios &Ratios, Hierarchy &Hierarchy, string Path) : ratios(Ratios), hierarchy(Hierarchy)
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
	added.clear();
	removed.clear();
	changes.clear();
	removing.clear();
***REMOVED***
	structures.resize(ratios.ids.size());
***REMOVED***
	// Fetch schemata from database
	vector<string> representatives;
	representatives.reserve(ratios.ids.size());
	for (size_t i = 0; i < ratios.ids.size(); ++i)
		if (ratios.names[i].size())
			representatives.push_back(*ratios.names[i].begin());
	auto result = Queries::Structures(representatives); // For some reason result has fever items than parameter
	
	for (auto i = result.begin(); i != result.end(); ++i) {
		auto j = ratios.ids.find(i->first);
		if (j != ratios.ids.end())
			structures[j->second] = i->second;
	}
***REMOVED***
	// Output
	if (Output) {
		// Count connections
		size_t fields = 0;
		for (auto i = structures.begin(); i != structures.end(); ++i)
			fields += i->size();
***REMOVED***
		// Print message
		cout << "Loaded " << fields << " fields." << endl;
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
	added.clear();
	removed.clear();
	changes.clear();
	removing.clear();
***REMOVED***
	// Initialize stream
	Deserialize in(Path);
	if (!in.Good())
		return false;
***REMOVED***
	// Read data
	in >> structures;
	in >> added;
	in >> removed;
	in >> changes;
	in >> removing;
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
	out << added;
	out << removed;
	out << changes;
	out << removing;
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
	added.resize(ratios.ids.size());
	removed.resize(ratios.ids.size());
	changes.resize(ratios.ids.size());
	removing.resize(ratios.ids.size());
***REMOVED***
	// Compute for each children of current table
	for (size_t i = 0; i < hierarchy.names.size(); ++i) {
		for (auto j = hierarchy.children[i].begin(); j != hierarchy.children[i].end(); ++j) {
			pair<unordered_set<string>, unordered_set<string>> difference = Difference(i, *j);
			added[*j]    = difference.first;
			removed[*j]  = difference.second;
			changes[*j]  = (float)(added[*j].size() + removed[*j].size()) / structures[*j].size();
			removing[*j] = (removed[*j].size() > 0);
		}
	}
}
***REMOVED***
// Compute added and removed fields between any two tables
pair<unordered_set<string>, unordered_set<string>> Structures::Difference(size_t Parent, size_t Child)
{
	pair<unordered_set<string>, unordered_set<string>> result;
***REMOVED***
	// Find added fields
	for (auto i = structures[Child].begin(); i != structures[Child].end(); ++i) {
		// Using the own find operator because find doesent use def. comperator
		if (std::find(structures[Parent].begin(), structures[Parent].end(), *i) == structures[Parent].end())
			result.first.insert(i->name);
	}
***REMOVED***
	// Find removed streams
	for (auto i = structures[Parent].begin(); i != structures[Parent].end(); ++i) {
		// Using the own find operator because find doesent use def. comperator
		if (std::find(structures[Child].begin(), structures[Child].end(), *i) == structures[Child].end())
			result.second.insert(i->name);
	}
***REMOVED***
	return result;
}
***REMOVED***
// Return cached difference for a child to its parent
pair<unordered_set<string>, unordered_set<string>> Structures::Difference(size_t Child)
{
	// Check for valid table
	if (Child > added.size() - 1 || Child > removed.size() - 1)
		throw exception("Table index out of range");
***REMOVED***
	return { added[Child], removed[Child] };
}

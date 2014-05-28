#include "algorithm/structures.h"
#include "helper/queries.h"
#include "helper/serialize.h"
using namespace std;
***REMOVED***
***REMOVED***
// Constructor checks dump and fetch data
Structures::Structures(Ratios &Ratios, string Dsn, string User, string Password, string Path) : ids(Ratios.ids)
{
	// Try to load dump
	
	if (Saved(Path) && Load(Path)) {
		cout << "Loaded cached schemata." << endl;
		return;
	}
***REMOVED***
	Fetch(Dsn, User, Password);
	if (structures.size())
		Save(Path);
}
***REMOVED***
// Fetch fields from database and build map from it
void Structures::Fetch(string Dsn, string User, string Password, bool Output)
{
	// Reset data
	structures.clear();
	
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
	// Reset data
	structures.clear();
***REMOVED***
	// Initialize stream
	Deserialize in(Path);
	if (!in.Good())
		return false;
***REMOVED***
	// Read data
	in >> structures;
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
// Calculate memory size in bytes
size_t Structures::Size()
{
	size_t size = 0;
***REMOVED***
	// Structures
	size += structures.size() * sizeof(size_t);
	for (auto i = structures.begin(); i != structures.end(); ++i)
		size += i->size() * (sizeof(size_t) + sizeof(Queries::Field));
***REMOVED***
	return size;
}
***REMOVED***
// Returns a set of fieldnames for a table
unordered_set<Queries::Field> Structures::Get(size_t Id)
{
	unordered_set<Queries::Field> empty_set;
	if (Id > ids.size())
		return empty_set;
	return structures[Id];
}
***REMOVED***
// Returns a differencwe between two tables
unordered_set<Queries::Field> Structures::Common(size_t Parent_Id, size_t Child_Id)
{
	// Get the fields of both tables
	unordered_set<Queries::Field> parent_set = Get(Parent_Id);
	unordered_set<Queries::Field> child_set = Get(Child_Id);
***REMOVED***
	unordered_set<Queries::Field> common;
	
	// Compare all fields in parent with child to find the ones in common
	for (auto field = parent_set.begin(); field != parent_set.end(); field++) {
		if (child_set.find(*field) != child_set.end())
			common.insert(*field);
	}
	
	return common;
}

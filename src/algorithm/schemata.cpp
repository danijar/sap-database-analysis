#include "algorithm/schemata.h"
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
	if (schemata.size())
		Save(Path);
}
***REMOVED***
// Fetch fields from database and build map from it
void Structures::Fetch(string Dsn, string User, string Password, bool Output)
{
	// Reset data
	schemata.clear();
	
	// Fetch schemata from database
	schemata = Queries::Structures(ids);
***REMOVED***
	// Output
	if (Output) {
		// Count connections
		size_t fields = 0;
		for (auto i = schemata.begin(); i != schemata.end(); ++i)
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
	schemata.clear();
***REMOVED***
	// Initialize stream
	Deserialize in(Path);
	if (!in.Good())
		return false;
***REMOVED***
	// Read data
	in >> schemata;
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
	out << schemata;
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
	size += schemata.size() * sizeof(size_t);
	for (auto i = schemata.begin(); i != schemata.end(); ++i)
		size += i->size() * (sizeof(size_t) + sizeof(Queries::Field));
***REMOVED***
	return size;
}
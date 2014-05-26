#include "schemata.h"
using namespace std;
***REMOVED***
// Constructor checks dump and fetch data
Schemata::Schemata(Input &Input, string Dsn, string User, string Password, string Path) : ids(Input.ids)
{
	// Load input data from database or dump
	if (Saved(Path))
		Load(Path);
	else {
		Fetch(Dsn, User, Password, true);
		if (schemata.size())
			Save(Path);
	}
}
***REMOVED***
// Fetch fields from database and build map from it
void Schemata::Fetch(string Dsn, string User, string Password, bool Output)
{
	// Reset data
	schemata.clear();
	
	// Fetch schemata from database
	schemata = Queries::Schemata(ids, Dsn, User, Password);
	
	// Output
	if (Output) {
		// Count connections
		size_t fields = 0;
		for (auto i = schemata.begin(); i != schemata.end(); ++i)
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
bool Schemata::Load(string Path)
{
	// Reset data
	ids.clear();
	schemata.clear();
***REMOVED***
	Deserialize in(Path);
	size_t size;
	size_t id;
	string name;
***REMOVED***
	// Ids
	in >> size;
	for (size_t i = 0; i < size; ++i) {
		in >> name >> id;
		ids.insert(make_pair(name, id));
	}
***REMOVED***
	
	// Schemata
	in >> size;
	for (size_t i = 0; i < size; ++i) {
		size_t key, length, pos;
		in >> key >> length;
***REMOVED***
		unordered_set<Queries::Field> value;
		string name, roll, domain;
		Queries::Field field;
		for (size_t j = 0; j < length; ++j) {
			// Read in field values and add to set
			in >> name >> domain >> roll;
			in >> pos;
			field.name		= name;
			field.domain	= domain;
			field.roll		= roll;
			field.position	= pos;
			value.insert(field);
		}
***REMOVED***
		schemata.insert(make_pair(key, value));
	}
***REMOVED***
	return true;
}
***REMOVED***
// Save current data to disk
bool Schemata::Save(string Path)
{
	Serialize out(Path);
***REMOVED***
	// Ids
	out << ids.size();
	for (auto i = ids.begin(); i != ids.end(); ++i)
		out << i->first << i->second;
***REMOVED***
	// Schemata
	out << schemata.size();
	for (auto i = schemata.begin(); i != schemata.end(); ++i) {
		out << i->first << i->second.size();
		for (auto j : i->second)
			out << j.name << j.domain << j.roll << j.position;		
	}
***REMOVED***
	return true;
}
***REMOVED***
// Check whether there is a dump file at this location
bool Schemata::Saved(string Path)
{
	ifstream stream(Path.c_str());
	bool result = stream.good();
	stream.close();
	return result;
}
***REMOVED***
// Calculate memory size in bytes
size_t Schemata::Size()
{
	size_t size = 0;
***REMOVED***
	// Ratios
	size += schemata.size() * sizeof(size_t);
	for (auto i = schemata.begin(); i != schemata.end(); ++i)
		size += i->second.size() * (sizeof(size_t) + sizeof(Queries::Field));
***REMOVED***
	return size;
}

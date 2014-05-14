#include "input.h"
***REMOVED***
#include <iostream>
#include <chrono>
***REMOVED***
using namespace std;
using namespace std::chrono;
***REMOVED***
***REMOVED***
// Constructor
Input::Input(string Dsn, string User, string Password, bool Output)
{
	// Measure execution time
	high_resolution_clock::time_point start;
	if (Output)
		start = high_resolution_clock::now();
***REMOVED***
	// Query rows from database
	auto rows = Query(Dsn, User, Password, Output);
***REMOVED***
	// Build ratio graph
	size_t counter = 0;
	for (auto i = rows.begin(); i != rows.end(); ++i) {
		// Create nodes
		size_t parent = Id(i->parent);
		size_t child = Id(i->child);
***REMOVED***
		// Create edges
		Ratio(parent, child, i->parentratio);
		Ratio(child, parent, i->childratio);
***REMOVED***
		// Output
		counter++;
		if (Output && counter % 10000 == 0)
			cout << ".";
	}
***REMOVED***
	// Output
	if (Output) {
		// End line
		cout << endl;
***REMOVED***
		// Calculate execution time
		long long time = duration_cast<chrono::milliseconds>(high_resolution_clock::now() - start).count();
***REMOVED***
		// Count connections
		size_t connections = 0;
		for (auto i = ratios.begin(); i != ratios.end(); ++i)
			connections += i->second.size();
***REMOVED***
		// Print message
		cout << "Loaded "
				<< ids.size() << " tables and "
				<< connections << " connections of "
				<< 0.001 * (1000 * Size() / 1024 / 1024) << "mb of memory in "
				<< 0.001 * time << "s."
				<< endl;
	}
}
***REMOVED***
// Get id of a table name
size_t Input::Id(string name)
{
	// Add if not already in map
	auto parentiterator = ids.find(name);
	if (parentiterator == ids.end()) {
		size_t id = ids.size();
		ids[name] = id;
		return id;
	}
***REMOVED***
	// Otherwise return existing
	else
		return parentiterator->second;
}
***REMOVED***
// Set ratios between two tables
void Input::Ratio(size_t From, size_t To, float Weight)
{
	// Create new start node if not existing
	auto i = ratios.find(From);
	if (i == ratios.end())
		ratios[From] = unordered_map<size_t, float>();
***REMOVED***
	// Set weight
	ratios[From][To] = Weight;
}
***REMOVED***
// Load input data from database into memory
vector<Input::row> Input::Query(string Dsn, string User, string Password, bool Output)
{
	vector<row> rows;
***REMOVED***
	// Initialize database driver
	otl_connect db;
	otl_connect::otl_initialize();
***REMOVED***
	try {
		// Connect to database
		string connect = "UID=" + User + ";PWD=" + Password + ";DSN=" + Dsn;
		db.rlogon(connect.c_str());
***REMOVED***
		// Select whole results table
		otl_stream select(50, "SELECT parent, child, parent_ratio, child_ratio FROM ABAP.RESULT", db);
***REMOVED***
		// Read input data into array
		while (!select.eof()) {
			row current;
			select >> current.parent >> current.child >> current.parentratio >> current.childratio;
			rows.push_back(current);
***REMOVED***
			// Output
			if (Output && rows.size() % 10000 == 0)
				cout << ".";
		}
***REMOVED***
		// Output end line
		if (Output)
			cout << endl;
	}
	catch (otl_exception& e) {
		// Print database errors
		cerr << e.msg << endl;
		cerr << e.stm_text << endl;
		cerr << e.sqlstate << endl;
		cerr << e.var_info << endl;
	}
***REMOVED***
	// Cleanup
	db.logoff();
***REMOVED***
	return rows;
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

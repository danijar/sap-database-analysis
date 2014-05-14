#include "input.h"
#include <iostream>
#include "bar.h"
using namespace std;
***REMOVED***
***REMOVED***
// Constructor
Input::Input(string Dsn, string User, string Password, bool Output)
{
	// Query rows from database
	auto rows = Query(Dsn, User, Password, Output);
	Graph(rows, Output);
***REMOVED***
	// Output
	if (Output) {
		// Count connections
		size_t connections = 0;
		for (auto i = ratios.begin(); i != ratios.end(); ++i)
			connections += i->second.size();
***REMOVED***
		// Print message
		cout << "Loaded "
				<< ids.size() << " tables and "
				<< connections << " connections stored in "
				<< 0.001 * (1000 * Size() / 1024 / 1024) << " megabytes of memory."
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
		// Count number of rows in result
		int count;
		otl_stream countquery;
		countquery.open(50, "SELECT COUNT(*) FROM ABAP.RESULT", db);
		countquery >> count;
***REMOVED***
		// Select whole results table
		otl_stream query(50, "SELECT parent, child, parent_ratio, child_ratio FROM ABAP.RESULT", db);
***REMOVED***
		// Read input data into array
		Bar bar("Query rows", count);
		while (!query.eof()) {
			row current;
			query >> current.parent >> current.child >> current.parentratio >> current.childratio;
			rows.push_back(current);
***REMOVED***
			// Output
			if (Output && rows.size() % 10000 == 0)
				bar.Increment(10000);
		}
***REMOVED***
		// Output end line
		if (Output)
			bar.Finish();
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
// Build ratio graph
void Input::Graph(vector<row> &Rows, bool Output)
{
	// Create graph from query rows
	size_t counter = 0;
	Bar bar("Unpack data", Rows.size());
	for (auto i = Rows.begin(); i != Rows.end(); ++i) {
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
			bar.Increment(10000);
	}
***REMOVED***
	// Output line end
	if (Output)
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

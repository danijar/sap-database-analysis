#include <iostream>
#include <string>
#include <vector>
#include <chrono>
***REMOVED***
#define OTL_ODBC
#define OTL_STL
#include "otlv4.h"
***REMOVED***
using namespace std;
using namespace std::chrono;
***REMOVED***
// Data structure to hold an input row
struct input_row
{
	char parent[32], child[32];
	float pratio, cratio;
};
***REMOVED***
vector<input_row> query_input_rows(otl_connect &db, bool output = false)
{
	// Measure execution time
	high_resolution_clock::time_point start;
	if (output)
		start = high_resolution_clock::now();
***REMOVED***
	// Select whole results table
	otl_stream select(50, "SELECT parent, child, parent_ratio, child_ratio FROM ABAP.RESULT", db);
***REMOVED***
	// Read input data into array
	vector<input_row> rows;
	while (!select.eof()) {
		input_row row;
		select >> row.parent >> row.child >> row.pratio >> row.cratio;
		rows.push_back(row);
***REMOVED***
		// Output
		if (output && rows.size() % 10000 == 0)
			cout << ".";
	}
***REMOVED***
	// Output
	if (output) {
		double elapsed = 0.001 * duration_cast<chrono::milliseconds>(high_resolution_clock::now() - start).count();
		double size = 0.001 * (1000 * sizeof input_row * rows.size() / 1024 / 1024);
		cout << endl;
		cout << "Successfully loaded " << rows.size() << " records of " << size << " megabytes in " << elapsed << " seconds." << endl;
	}
***REMOVED***
	return rows;
}
***REMOVED***
size_t query_table_count(otl_connect &db, bool output = false)
{
	// Measure execution time
	high_resolution_clock::time_point start;
	if (output)
		start = high_resolution_clock::now();
***REMOVED***
	// Execute query
	otl_stream query;
	query.open(50,
		"SELECT COUNT(*) FROM ("
		"SELECT DISTINCT PARENT FROM ABAP.RESULT "
		"UNION "
		"SELECT DISTINCT CHILD FROM ABAP.RESULT"
		")", db);
***REMOVED***
	// Get result
	int count;
	query >> count;
***REMOVED***
	// Output
	if (output) {
		long long elapsed = duration_cast<milliseconds>(high_resolution_clock::now() - start).count();
		cout << "Table count " << count << " determined in " << elapsed << " milliseconds." << endl;
	}
***REMOVED***
	return count;
}
***REMOVED***
vector<string> query_tables(otl_connect &db, bool output = false)
{
	// Measure execution time
	high_resolution_clock::time_point start;
	if (output)
		start = high_resolution_clock::now();
***REMOVED***
	// Execute query
	otl_stream query;
	query.open(50,
		"SELECT TABLE FROM ("
		"SELECT DISTINCT PARENT AS TABLE FROM ABAP.RESULT "
		"UNION "
		"SELECT DISTINCT CHILD AS TABLE FROM ABAP.RESULT"
		")", db);
***REMOVED***
	// Get results and append to vector
	vector<string> tables;
	string name;
	while (!query.eof()) {
		query >> name;
		tables.push_back(name);
	}
***REMOVED***
	// Output
	if (output) {
		double elapsed = 0.001 * duration_cast<milliseconds>(high_resolution_clock::now() - start).count();
***REMOVED***
		size_t bytes = 0;
		for (auto i : tables) {
			bytes += i.length();
			cout << i << endl;
		}
		cout << endl;
***REMOVED***
		double size = 0.001 * (1000 * bytes / 1024);
		cout << "Found " << tables.size() << " tables of " << size << " kilobytes in " << elapsed << " seconds." << endl;
	}
***REMOVED***
	return tables;
}
***REMOVED***
int main()
{
	// Initialize database driver
	otl_connect db;
	otl_connect::otl_initialize();
***REMOVED***
	try {
		// Connect to database
		db.rlogon("***REMOVED***;***REMOVED***;***REMOVED***");
***REMOVED***
		// Execuzte queries
		query_table_count(db, true);
		cin.get();
***REMOVED***
		query_tables(db, true);
		cin.get();
***REMOVED***
		query_input_rows(db, true);
		cin.get();
	}
	catch (otl_exception& e) {
		// Print database errors
		cerr << e.msg << endl;
		cerr << e.stm_text << endl;
		cerr << e.sqlstate << endl;
		cerr << e.var_info << endl;
	}
***REMOVED***
	// Cleanup and hold console open
	db.logoff();
	cin.get();
	return 0;
}

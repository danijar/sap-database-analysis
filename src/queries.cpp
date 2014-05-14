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
***REMOVED***
size_t query_table_count(bool output = false)
{
	int count;
***REMOVED***
	// Initialize database driver
	otl_connect db;
	otl_connect::otl_initialize();
***REMOVED***
	// Measure execution time
	high_resolution_clock::time_point start;
	if (output)
		start = high_resolution_clock::now();
***REMOVED***
	try {
		// Connect to database
		db.rlogon("***REMOVED***;***REMOVED***;***REMOVED***");
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
		query >> count;
***REMOVED***
		// Output
		if (output) {
			long long elapsed = duration_cast<milliseconds>(high_resolution_clock::now() - start).count();
			cout << "Table count " << count << " determined in " << elapsed << " milliseconds." << endl;
		}
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
	return count;
}
***REMOVED***
***REMOVED***
vector<string> query_tables(bool output = false)
{
	vector<string> tables;
***REMOVED***
	// Initialize database driver
	otl_connect db;
	otl_connect::otl_initialize();
***REMOVED***
	// Measure execution time
	high_resolution_clock::time_point start;
	if (output)
		start = high_resolution_clock::now();
***REMOVED***
	try {
		// Connect to database
		db.rlogon("***REMOVED***;***REMOVED***;***REMOVED***");
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
	return tables;
}

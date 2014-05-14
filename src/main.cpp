#include <iostream>
#include <string>
#include <vector>
#include <chrono>
***REMOVED***
#define OTL_ODBC
#include "otlv4.h"
***REMOVED***
using namespace std;
using namespace std::chrono;
***REMOVED***
// Data structure to hold a row
struct Row
{
	char parent[32], child[32];
	float pratio, cratio;
};
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
		// Select whole results table
		otl_stream select(50, "SELECT parent, child, parent_ratio, child_ratio FROM ABAP.RESULT", db);
		
		// Read input data into array
		vector<Row> rows;
		auto start = high_resolution_clock::now();
		while (!select.eof()) {
			Row row;
			select >> row.parent >> row.child >> row.pratio >> row.cratio;
			rows.push_back(row);
			if (rows.size() % 10000 == 0)
				cout << ".";
		}
		cout << endl;
***REMOVED***
		// Print metrics
		double elapsed = 0.001 * chrono::duration_cast<chrono::milliseconds>(high_resolution_clock::now() - start).count();
		double size = 0.001 * (1000 * sizeof Row * rows.size() / 1024 / 1024);
		cout << "Successfully loaded " << rows.size() << " records of " << size << " megabytes in " << elapsed << " seconds." << endl;
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

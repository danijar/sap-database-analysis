#include <iostream>
#include <string>
***REMOVED***
#define OTL_ODBC
#include "otlv4.h"
***REMOVED***
using namespace std;
***REMOVED***
int main()
{
	// Initialize database driver
	otl_connect db;
	otl_connect::otl_initialize();
***REMOVED***
	try {
		// Connect to database
		db.rlogon("UID=***REMOVED***;PWD=***REMOVED***;DSN=HANA");
***REMOVED***
		// Select from results table
		otl_stream select(50, "SELECT parent, child, parent_ratio, child_ratio FROM ABAP.RESULT LIMIT 5", db);
***REMOVED***
		// Variables to hold field values of a row
		char parent[32], child[32];
		float pratio, cratio;
***REMOVED***
		// Read and print result set row by row
		while (!select.eof()) {
			select >> parent >> child >> pratio >> cratio;
			cout << parent << " " << child  << " " << pratio << " " << cratio << endl;
		}
***REMOVED***
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

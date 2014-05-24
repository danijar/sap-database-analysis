#include "queries.h"
#define OTL_ODBC
#define OTL_STL
#include "otlv4.h"
using namespace std;
***REMOVED***
***REMOVED***
namespace Queries {
	// Get fields of a table from DDO3L
	unordered_set<string> Scheme(string Table)
	{
		unordered_set<string> fields;
***REMOVED***
		// Initialize database driver
		otl_connect db;
		otl_connect::otl_initialize();
***REMOVED***
		try {
			// Connect to database
			string connect = "***REMOVED***;***REMOVED***;***REMOVED***";
			db.rlogon(connect.c_str());
***REMOVED***
			// Select scheme from table
			string text = "SELECT FIELDNAME FROM ABAP.DD03L WHERE TABNAME = '" + Table + "' ORDER BY POSITION ASC";
			otl_stream query(50, text.c_str(), db);
***REMOVED***
			// Read input data into array
			while (!query.eof()) {
				string field;
				query >> field;
				fields.insert(field);
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
		return fields;
	}
}

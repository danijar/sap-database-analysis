#include "helper/queries.h"
#define OTL_ODBC
#define OTL_STL
#include "otlv4.h"
using namespace std;
***REMOVED***
***REMOVED***
namespace Queries {
	// Load input data from database into memory
	vector<Ratio> Ratios()
	{
		vector<Ratio> rows;
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
			countquery.open(50, "SELECT COUNT(*) FROM ABAP.RESULT_V1", db);
			countquery >> count;
***REMOVED***
			// Skip if empty
			if (!count) {
				cout << "No records found." << endl;
				return rows;
			}
***REMOVED***
			// Select whole results table
			otl_stream query(50, "SELECT parent, child, parent_ratio, child_ratio FROM ABAP.RESULT_V1", db);
***REMOVED***
			// Read input data into array
			Bar bar("Query ratios", count);
			while (!query.eof()) {
				Ratio ratio;
				query >> ratio.parent >> ratio.child >> ratio.parentratio >> ratio.childratio;
				rows.push_back(ratio);
				bar.Increment();
			}
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
	// Serializer for query field type
	Serialize &operator<<(Serialize &serialize, const Queries::Field &field)
	{
		serialize << field.name << field.roll << field.domain << field.position;
		return serialize;
	}
***REMOVED***
	// Deserializer for query field type
	Deserialize &operator>>(Deserialize &deserialize, Queries::Field &field)
	{
		deserialize >> field.name >> field.roll >> field.domain >> field.position;
		return deserialize;
	}
***REMOVED***
	// Load field data from database into memory for certain table
	vector<Field> Fields(string Table)
	{
		vector<Field> rows;
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
			// Count number of fields in result
			int count;
			otl_stream countquery;
			string count_query = "SELECT COUNT(*) FROM ABAP.DD03L WHERE TABNAME = '" + Table + "'";
			countquery.open(50, count_query.c_str(), db);
			countquery >> count;
***REMOVED***
			// Skip if empty
			if (!count) {
				cout << "No records found." << endl;
				return rows;
			}
***REMOVED***
			// Select fields for the table
			string select_query = "SELECT fieldname, rollname, domname, position FROM ABAP.DD03L WHERE TABNAME = '" + Table + "'";
			otl_stream query(50, select_query.c_str(), db);
***REMOVED***
			// Read input data into array
			Bar bar("Query fields", count);
			while (!query.eof()) {
				Field current;
				string position;
				query >> current.name >> current.roll >> current.domain >> position;
				current.position = (size_t)stoi(position);
				rows.push_back(current);
				bar.Increment();
			}
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
	// Load the scemata of a set of tables from the database
	unordered_map<string, unordered_set<Field>> Structures(std::unordered_set<string> &Names)
	{
		unordered_map<string, unordered_set<Field>> result;
***REMOVED***
		// Building table list for query
		string table_list;
		bool first = true;
		for (auto name = Names.begin(); name != Names.end(); name++) {
			if (first) {
				table_list += "'" + *name + "'";
				first = false;
			}
			else table_list += ", '" + *name + "'";
		}
		
		// Initialize database driver
		otl_connect db;
		otl_connect::otl_initialize();
***REMOVED***
		try {
			// Connect to database
			string connect = "UID=" + User + ";PWD=" + Password + ";DSN=" + Dsn;
			db.rlogon(connect.c_str());
***REMOVED***
			// Count number of fields in result
			int count;
			otl_stream countquery;
			string count_query = "SELECT COUNT(*) FROM ABAP.DD03L WHERE TABNAME IN (" + table_list + ")";
			countquery.open(50, count_query.c_str(), db);
			countquery >> count;
***REMOVED***
			// Skip if empty
			if (!count) {
				cout << "No records found." << endl;
				return result;
			}
***REMOVED***
			// Select fields for the table
			string select_query = "SELECT tabname, fieldname, rollname, domname, position FROM ABAP.DD03L WHERE TABNAME IN (" + table_list + ")";
			otl_stream query(50, select_query.c_str(), db);
***REMOVED***
			// Read input data into array
			Bar bar("Query structures", count);
			
			while (!query.eof()) {
				Field current;
				string table, position;
				query >> table >> current.name >> current.roll >> current.domain >> position;
				current.position = (size_t)stoi(position);
				
				// Find corresponding id and add to result
				auto i = Names.find(table);
				if (i != Names.end())
					result[*i].insert(current);
***REMOVED***
				bar.Increment();
			}
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
		
		return result;
	}
}

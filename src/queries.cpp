#include "queries.h"
#define OTL_ODBC
#define OTL_STL
#include "otlv4.h"
using namespace std;
***REMOVED***
***REMOVED***
namespace Queries {
	// Get fields of a table from DDO3L
	unordered_set<string> Schema(string Table)
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
***REMOVED***
	// Load input data from database into memory
	vector<ratio_row> Ratios(string Dsn, string User, string Password)
	{
		vector<ratio_row> rows;
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
				ratio_row current;
				query >> current.parent >> current.child >> current.parentratio >> current.childratio;
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
	vector<Field> Fields(string Table, string Dsn, string User, string Password)
	{
		vector<Field> field_rows;
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
				return field_rows;
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
				field_rows.push_back(current);
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
		return field_rows;
	}
***REMOVED***
	// Load the scemata of a set of tables from the database
	unordered_map<size_t, unordered_set<Field>> Schemata(unordered_map<string, size_t> &Ids, string Dsn, string User, string Password)
	{
		unordered_map<size_t, unordered_set<Field>> result;
***REMOVED***
		// Building table list for query
		string table_list;
		bool first = true;
		for (auto name = Ids.begin(); name != Ids.end(); name++) {
			if (first) {
				table_list += "'" + name->first + "'";
				first = false;
			}
			else table_list += ", '" + name->first + "'";
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
			Bar bar("Query schemata", count);
			while (!query.eof()) {
				Field current;
				string table, position;
				query >> table >> current.name >> current.roll >> current.domain >> position;
				current.position = (size_t)stoi(position);
				
				// Add field into result table if name is in result table
				auto i = Ids.find(table);
				if (i != Ids.end())
					result[i->second].insert(current);
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

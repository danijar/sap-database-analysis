#include "helper/queries.h"
#define OTL_ODBC
#define OTL_STL
#include "otlv4.h"
#include "helper/jsonize.h"
using namespace std;
***REMOVED***
***REMOVED***
namespace Queries {
	// Serializer for ratio type
	Serialize &operator<<(Serialize &serialize, const Queries::Ratio &ratio)
	{
		serialize << ratio.parent << ratio.child << ratio.parentratio << ratio.childratio;
		return serialize;
	}
***REMOVED***
	// Deserializer for ratio type
	Deserialize &operator>>(Deserialize &deserialize, Queries::Ratio &ratio)
	{
		deserialize >> ratio.parent >> ratio.child >> ratio.parentratio >> ratio.childratio;
		return deserialize;
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
	unordered_map<string, unordered_set<Field>> Structures(vector<string> &Names)
	{
		unordered_map<string, unordered_set<Field>> result;
***REMOVED***
		// Building table list for query
		string table_list;
		bool first = true;
		for (auto i = Names.begin(); i != Names.end(); ++i) {
			if (first) {
				table_list += "'" + *i + "'";
				first = false;
			} else {
				table_list += ", '" + *i + "'";
			}
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
			result.reserve(count);
			while (!query.eof()) {
				Field current;
				string table, position;
				query >> table >> current.name >> current.roll >> current.domain >> position;
				current.position = (size_t)stoi(position);
				
				// Find corresponding id and add to result
				result[table].insert(current);
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
***REMOVED***
	bool Store(size_t Id, unordered_map<size_t, float> &Ratios, unordered_set<string> &Names, unordered_set<size_t> &Children, size_t Amount, unordered_set<string> &Added, unordered_set<string> &Removed)
	{
		// Initialize database driver
		otl_connect db;
		otl_connect::otl_initialize();
***REMOVED***
		try {
			// Connect to database
			string connect = "UID=" + User + ";PWD=" + Password + ";DSN=" + Dsn;
			db.rlogon(connect.c_str());
***REMOVED***
			// Set up table
			string table = "ABAP.ANALYSIS";
			string length = "1000";
			otl_cursor::direct_exec(db, string("DROP TABLE " + table).c_str());
			otl_cursor::direct_exec(db, string("CREATE TABLE " + table + " (id INT, ratios VARCHAR(" + length + "), names VARCHAR(" + length + "), children VARCHAR(" + length + "), amount INT, added VARCHAR(" + length + "), removed VARCHAR(" + length + "), PRIMARY KEY(id))").c_str());
			db.commit();
***REMOVED***
			// Generate query
			string query_string = "INSERT INTO " + table + " (id, ratios, names, children, amount, differences) VALUES (";
			Jsonize json;
			query_string += to_string(Id) + ", ";
			json << Ratios;
			query_string += "'" + json.Dissolve() + "', ";
			json << Names;
			query_string += "'" + json.Dissolve() + "', ";
			json << Children;
			query_string += "'" + json.Dissolve() + "', ";
			query_string += to_string(Amount) + ", ";
			json << Added;
			query_string += "'" + json.Dissolve() + "', ";
			json << Removed;
			query_string += "'" + json.Dissolve() + "')";
			
			// Insert row
			otl_stream query(50, query_string.c_str(), db);
			query.flush();
		}
***REMOVED***
		catch (otl_exception& e) {
			// Print database errors
			cerr << e.msg << endl;
			cerr << e.stm_text << endl;
			cerr << e.sqlstate << endl;
			cerr << e.var_info << endl;
			return false;
		}
***REMOVED***
		// Cleanup
		db.logoff();
		return true;
	}
}

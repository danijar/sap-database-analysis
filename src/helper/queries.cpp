#include "helper/queries.h"
#define OTL_ODBC
#define OTL_STL
#include "otlv4.h"
#include "helper/jsonize.h"
using namespace std;
***REMOVED***
***REMOVED***
namespace Queries {
	// Connect to database and execute given query
	bool Query(string Querystring)
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
			// Execute query
			otl_stream query(50, Querystring.c_str(), db);
			query.flush();
***REMOVED***
			// Cleanup
			db.logoff();
			return true;
		}
		catch (otl_exception& e) {
			// Print database errors
			cerr << e.msg << endl;
			cerr << e.stm_text << endl;
			cerr << e.sqlstate << endl;
			cerr << e.var_info << endl;
***REMOVED***
			// Cleanup
			db.logoff();
			return false;
		}
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
	void Table(string Name, string Columns)
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
			// Drop table if exists
			try {
				otl_cursor::direct_exec(db, string("DROP TABLE " + Name).c_str());
				db.commit();
			}
			catch (otl_exception&) {}
***REMOVED***
			// Create new table
			otl_cursor::direct_exec(db, string("CREATE COLUMN TABLE " + Name + " (" + Columns + ")").c_str());
			db.commit();
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
	}
	
	void Create()
	{
		// Create table schema for storing results
		Table("ABAP.ANALYSIS_META",     "id INT, amount INT, ratio FLOAT, changes FLOAT, removing BINARY, PRIMARY KEY(id)");
		Table("ABAP.ANALYSIS_NAMES",    "id INT, name VARCHAR(128)");
		Table("ABAP.ANALYSIS_CHILDREN", "id INT, child INT");
		Table("ABAP.ANALYSIS_ADDED",    "id INT, field VARCHAR(128)");
		Table("ABAP.ANALYSIS_REMOVED",  "id INT, field VARCHAR(128)");
	}
***REMOVED***
	bool Store(size_t Id, unordered_map<size_t, float> &Ratios, unordered_set<string> &Names, unordered_set<size_t> &Children, size_t Amount, unordered_set<string> &Added, unordered_set<string> &Removed)
	{		
		Query("INSERT INTO ABAP.ANALYSIS_META (id, amount) VALUES (" + to_string(Id) + ", " + to_string(Amount) + ")");
		
		for (auto i = Names.begin(); i != Names.end(); ++i)
			Query("INSERT INTO ABAP.ANALYSIS_NAMES (id, name) VALUES (" + to_string(Id) + ", '" + *i + "')");
***REMOVED***
		for (auto i = Children.begin(); i != Children.end(); ++i)
			Query("INSERT INTO ABAP.ANALYSIS_CHILDREN (id, child) VALUES (" + to_string(Id) + ", " + to_string(*i) + ")");
			
		for (auto i = Added.begin(); i != Added.end(); ++i)
			Query("INSERT INTO ABAP.ANALYSIS_ADDED (id, field) VALUES (" + to_string(Id) + ", '" + *i + "')");
***REMOVED***
		for (auto i = Removed.begin(); i != Removed.end(); ++i)
			Query("INSERT INTO ABAP.ANALYSIS_REMOVED (id, field) VALUES (" + to_string(Id) + ", '" + *i + "')");
***REMOVED***
		return true;
	}
}

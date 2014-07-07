#include "helper/queries.h"
#include "helper/jsonize.h"
using namespace std;
***REMOVED***
***REMOVED***
namespace Queries {
	// Ensure that a database connection is established
	void Connection()
	{
		// Return if already connected
		if (connected)
			return;
		
		// Connect to database
		try {
			otl_connect::otl_initialize();
			string connect = "UID=" + User + ";PWD=" + Password + ";DSN=" + Dsn;
			db.rlogon(connect.c_str());
			db.auto_commit_on();
			connected = true;
		}
		catch (...) {
			connected = false;
		}
	}
***REMOVED***
	// Create query from string
	// If it has no unbound parameters, directly execute it catching errors
	shared_ptr<otl_stream> Query(string Querystring, int Batchsize)
	{
		// Ensure connection
		Connection();
***REMOVED***
		try {		
			// Create query
			otl_stream *query = new otl_stream(Batchsize, Querystring.c_str(), db);
			return shared_ptr<otl_stream>(query);
		}
		catch (otl_exception& e) {
			// Print database errors
			cerr << e.msg << endl;
			cerr << e.stm_text << endl;
			cerr << e.sqlstate << endl;
			cerr << e.var_info << endl;
			return shared_ptr<otl_stream>();
		}
	}
***REMOVED***
	bool Flush(otl_stream Query)
	{
		try {
			// Execute query
			Query.flush();
			return true;
		}
		catch (otl_exception& e) {
			// Print database errors
			cerr << e.msg << endl;
			cerr << e.stm_text << endl;
			cerr << e.sqlstate << endl;
			cerr << e.var_info << endl;
			return false;
		}
	}
***REMOVED***
	// Load input data from database into memory
	vector<Ratio> Ratios()
	{
		vector<Ratio> rows;
***REMOVED***
		// Count number of rows
		int count = 0;
		*Query("SELECT COUNT(*) FROM ABAP.RESULT_V1") >> count;
		if (!count) {
			cerr << "No ratios found in database." << endl;
			return rows;
		}
***REMOVED***
		// Read results table into array
		auto query = Query("SELECT parent, child, parent_ratio, child_ratio FROM ABAP.RESULT_V1");
		for (Bar bar("Query ratios", count); !query->eof(); bar++) {
			Ratio ratio;
			*query >> ratio.parent >> ratio.child >> ratio.parentratio >> ratio.childratio;
			rows.push_back(ratio);
		}
***REMOVED***
		return rows;
	}
***REMOVED***
	// Load field data from database into memory for certain table
	vector<Field> Fields(string Table)
	{
		vector<Field> rows;
***REMOVED***
		// Count number of fields in result
		int count;
		*Query("SELECT COUNT(*) FROM ABAP.DD03L WHERE TABNAME = '" + Table + "'") >> count;
		if (!count) {
			cerr << "No fields found in database." << endl;
			return rows;
		}
***REMOVED***
		// Read fields into array
		auto query = Query("SELECT fieldname, rollname, domname, position FROM ABAP.DD03L WHERE TABNAME = '" + Table + "'");
		for (Bar bar("Query fields", count); !query->eof(); bar++) {
			Field current;
			string position;
			*query >> current.name >> current.roll >> current.domain >> position;
			current.position = (size_t)stoi(position);
			rows.push_back(current);
		}
		
		return rows;
	}
***REMOVED***
	// Load the scemata of a set of tables from the database
	unordered_map<string, unordered_set<Field>> Structures(vector<string> &Names)
	{
		unordered_map<string, unordered_set<Field>> result;
***REMOVED***
		// Build table list for query
		string tables = "'" + *Names.begin() + "'";
		for (auto i = ++Names.begin(); i != Names.end(); ++i)
			tables += ", '" + *i + "'";
		
		// Count number of result fields
		int count;
		*Query("SELECT COUNT(*) FROM ABAP.DD03L WHERE TABNAME IN (" + tables + ")") >> count;
		if (!count) {
			cerr << "No structures found in database." << endl;
			return result;
		}
***REMOVED***
		// Read structures into array
		result.reserve(count);
		auto query = Query("SELECT tabname, fieldname, rollname, domname, position FROM ABAP.DD03L WHERE TABNAME IN (" + tables + ")");
		for (Bar bar("Query structures", count); !query->eof(); bar++) {
			Field current;
			string table, position;
			*query >> table >> current.name >> current.roll >> current.domain >> position;
			current.position = (size_t)stoi(position);
			result[table].insert(current);
		}
		
		return result;
	}
***REMOVED***
	void Table(string Name, string Columns)
	{
		// Drop table if exists
		try { Query("DROP TABLE " + Name); } catch (otl_exception&) {}
***REMOVED***
		// Create new table
		Query("CREATE COLUMN TABLE " + Name + " (" + Columns + ")");
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

#include "helper/queries.h"
#include "helper/jsonize.h"
using namespace std;


namespace Queries {
	// Ensure that a database connection is established
	void Connection()
	{
		// Return if already connected
		if (db.connected)
			return;
		
		// Connect to database
		try {
			otl_connect::otl_initialize();
			string connect = "UID=" + User + ";PWD=" + Password + ";DSN=" + Dsn;
			db.rlogon(connect.c_str());
			db.auto_commit_on();
		} catch (...) {}
	}

	// Create query from string
	// If it has no unbound parameters, directly execute it catching errors
	shared_ptr<otl_stream> Query(string QueryString, size_t BatchSize, bool ErrorOutput)
	{
		// Ensure connection
		Connection();

		// Create query
		shared_ptr<otl_stream> result;
		Catch([&] {
			otl_stream *query = new otl_stream((int)BatchSize, QueryString.c_str(), db);
			result = shared_ptr<otl_stream>(query);
		});
		return result;
	}

	bool Catch(function<void()> Callback)
	{
		try {
			// Run code
			Callback();
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

	// Load input data from database into memory
	vector<Ratio> Ratios()
	{
		vector<Ratio> rows;

		// Count number of rows
		int count = 0;
		*Query("SELECT COUNT(*) FROM " + DBSchema + "." + InputTable) >> count;
		if (!count) {
			cerr << "No ratios found in database." << endl;
			return rows;
		}

		// Read results table into array
		auto query = Query("SELECT parent, child, parent_ratio, child_ratio FROM " + DBSchema + "." + InputTable + " ORDER BY (parent_ratio + child_ratio) DESC, parent, child");
		for (Bar bar("Query ratios", count); !query->eof(); bar++) {
			Ratio ratio;
			*query >> ratio.parent >> ratio.child >> ratio.parentratio >> ratio.childratio;
			rows.push_back(ratio);
		}

		return rows;
	}

	// Load field data from database into memory for certain table
	vector<Field> Fields(string Table)
	{
		vector<Field> rows;

		// Count number of fields in result
		int count;
		*Query("SELECT COUNT(*) FROM " + DBSchema + "." + FieldsTable + " WHERE TABNAME = '" + Table + "'") >> count;
		if (!count) {
			cerr << "No fields found in database." << endl;
			return rows;
		}

		// Read fields into array
		auto query = Query("SELECT fieldname, rollname, domname, position FROM " + DBSchema + "." + FieldsTable + " WHERE TABNAME = '" + Table + "'");
		for (Bar bar("Query fields", count); !query->eof(); bar++) {
			Field current;
			string position;
			*query >> current.name >> current.roll >> current.domain >> position;
			current.position = (size_t)stoi(position);
			rows.push_back(current);
		}
		
		return rows;
	}

	// Load the scemata of a set of tables from the database
	unordered_map<string, unordered_set<Field>> Structures(vector<string> &Names)
	{
		unordered_map<string, unordered_set<Field>> result;

		// Build table list for query
		string tables = "";
		for (auto i = Names.begin(); i != Names.end(); ++i)
			tables += "'" + *i + "'" + (i != --Names.end() ? ", " : "");

		// Count number of result fields
		int count;
		*Query("SELECT COUNT(*) FROM " + DBSchema + "." + FieldsTable + " WHERE TABNAME IN (" + tables + ")") >> count;
		if (!count) {
			cerr << "No structures found in database." << endl;
			return result;
		}

		// Read structures into array
		result.reserve(count);
		auto query = Query("SELECT tabname, fieldname, rollname, domname, position FROM " + DBSchema + "." + FieldsTable + " WHERE TABNAME IN (" + tables + ")");
		for (Bar bar("Query structures", count); !query->eof(); bar++) {
			Field current;
			string table, position;
			*query >> table >> current.name >> current.roll >> current.domain >> position;
			current.position = (size_t)stoi(position);
			result[table].insert(current);
		}
		
		return result;
	}

	void Table(string Name, string Columns)
	{
		// Drop table if exists
		try { Query("DROP TABLE " + Name, 1, false); } catch (otl_exception&) {}

		// Create new table
		Query("CREATE COLUMN TABLE " + Name + " (" + Columns + ")");
	}
	
	void Create()
	{
		// Create table schema for storing results
		const string prefix = DBSchema + "." + OutputPrefix;
		Table(prefix + "_META",     "id INT, amount INT, ratio FLOAT, changes FLOAT, removing TINYINT, PRIMARY KEY(id)");
		Table(prefix + "_NAMES",    "id INT, name VARCHAR(128)");
		Table(prefix + "_CHILDREN", "id INT, child INT");
		Table(prefix + "_ADDED",    "id INT, field VARCHAR(128)");
		Table(prefix + "_REMOVED",  "id INT, field VARCHAR(128)");
	}

	bool Store(size_t Id,
		unordered_set<string> &Names,
		unordered_set<size_t> &Children,
		unordered_set<string> &Added,
		unordered_set<string> &Removed,
		size_t Amount,
		float Ratio,
		float Changes,
		bool Removing)
	{
		int id = (int)Id;

		const string prefix = DBSchema + "." + OutputPrefix;
		const size_t bulksize = 500;

		bool result = Catch([&] {
			static auto meta = Query("INSERT INTO " + prefix + "_META VALUES (:id<int>, :amount<int>, :ratio<float>, :changes<float>, :removing<int>)", 1);
			*meta << id << (int)Amount << Ratio << Changes << (Removing ? 1 : 0) << endr;
			
			static auto names = Query("INSERT INTO " + prefix + "_NAMES VALUES (:id<int>, :name<char[128]>)", bulksize);
			for (auto i = Names.begin(); i != Names.end(); ++i)
				*names << id << *i << endr;

			static auto children = Query("INSERT INTO " + prefix + "_CHILDREN VALUES (:id<int>, :child<int>)", bulksize);
			for (auto i = Children.begin(); i != Children.end(); ++i)
				*children << id << (int)*i << endr;
		
			static auto added = Query("INSERT INTO " + prefix + "_ADDED VALUES (:id<int>, :field<char[128]>)", bulksize);
			for (auto i = Added.begin(); i != Added.end(); ++i)
				*added << id << *i << endr;

			static auto removed = Query("INSERT INTO " + prefix + "_REMOVED VALUES (:id<int>, :field<char[128]>)", bulksize);
			for (auto i = Removed.begin(); i != Removed.end(); ++i)
				*removed << id << *i << endr;
		});

		return result;
	}
}

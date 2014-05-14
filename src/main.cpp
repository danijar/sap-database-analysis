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
void query_rows(otl_connect &db)
{
	// Data structure to hold a row
	struct Row
	{
		char parent[32], child[32];
		float pratio, cratio;
	};
***REMOVED***
	// Select whole results table
	otl_stream select(50, "SELECT parent, child, parent_ratio, child_ratio FROM ABAP.RESULT", db);
***REMOVED***
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
***REMOVED***
int query_tables_count(otl_connect &db)
{
	// Execute query
	otl_stream query;
	query.open(50,
		"SELECT COUNT(DISTINCT TABLE) FROM ("
		"SELECT PARENT AS TABLE FROM ABAP.RESULT "
		"UNION "
		"SELECT CHILD AS TABLE FROM ABAP.RESULT"
		")", db);
***REMOVED***
	// Get result
	int count;
	query >> count;
	return count;
}
***REMOVED***
vector<string> query_tables(otl_connect &db)
{
	vector<string> tables;
***REMOVED***
	// Execute query
	otl_stream query;
	query.open(50,
		"SELECT DISTINCT TABLE FROM ("
		"SELECT PARENT AS TABLE FROM ABAP.RESULT "
		"UNION "
		"SELECT CHILD AS TABLE FROM ABAP.RESULT"
		")", db);
***REMOVED***
	// Get results and append to vector
	string name;
	while (!query.eof()) {
		query >> name;
		tables.push_back(name);
	}
***REMOVED***
	return tables;
}
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
		/*
		// Execute query
		auto tables = query_tables(db);
		for (auto i : tables)
			cout << i << endl;
		*/
***REMOVED***
		query_rows(db);
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

#pragma once
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#define OTL_ODBC
#define OTL_STL
#include "otlv4.h"
#include "type/field.h"
#include "type/ratio.h"
#include "helper/bar.h"
***REMOVED***
/*
 * This namespace holds all code that connects to the database.
 */
namespace Queries {
	using namespace std;
***REMOVED***
	// Global connection information
	static string Dsn = "***REMOVED***";
	static string User = "***REMOVED***";
	static string Password = "***REMOVED***";
	static otl_connect db;
	static bool connected = false;
***REMOVED***
	// Helper functions
	void Connection();
	shared_ptr<otl_stream> Query(string Querystring, int Batchsize = 1);
	bool Flush(otl_stream Query);
***REMOVED***
	// Fetching functions
	vector<Ratio> Ratios();
	vector<Field> Fields(string Table);
	unordered_map<string, unordered_set<Field>> Structures(vector<string> &Names);
***REMOVED***
	// Inserting functions
	void Table(string Name, string Columns);
	void Create();
	bool Store(size_t Id, unordered_map<size_t, float> &Ratios, unordered_set<string> &Names, unordered_set<size_t> &Children, size_t Amount, unordered_set<string> &Added, unordered_set<string> &Removed);
}

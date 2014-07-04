#pragma once
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "type/field.h"
#include "type/ratio.h"
#include "helper/bar.h"
***REMOVED***
***REMOVED***
/*
 * This namespace holds all code that connects to the database.
 */
namespace Queries {
	using namespace std;
***REMOVED***
	// Global connection details
	static string Dsn = "***REMOVED***";
	static string User = "***REMOVED***";
	static string Password = "***REMOVED***";
***REMOVED***
	// Fetching functions
	vector<Ratio> Ratios();
	vector<Field> Fields(string Table);
	unordered_map<string, unordered_set<Field>> Structures(vector<string> &Names);
***REMOVED***
	// Inserting functions
	void Create(string Table, string Columns);
	bool Store(size_t Id, unordered_map<size_t, float> &Ratios, unordered_set<string> &Names, unordered_set<size_t> &Children, size_t Amount, unordered_set<string> &Added, unordered_set<string> &Removed);
}

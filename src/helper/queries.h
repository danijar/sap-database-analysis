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

/*
 * This namespace holds all code that connects to the database.
 */
namespace Queries {
	using namespace std;

	// Global connection information
	static string Dsn		= "";
	static string User		= "";
	static string Password	= "";

	static string DBSchema		= "";
	static string InputTable	= "";
	static string FieldsTable	= "";
	static string OutputPrefix	= "";

	static otl_connect db;

	// Helper functions
	void Connection();
	shared_ptr<otl_stream> Query(string QueryString, size_t BatchSize = 1, bool ErrorOutput = true);
	bool Catch(function<void()> Callback);

	// Fetching functions
	vector<Ratio> Ratios();
	vector<Field> Fields(string Table);
	unordered_map<string, unordered_set<Field>> Structures(vector<string> &Names);

	// Inserting functions
	void Table(string Name, string Columns);
	void Create();
	bool Store(
		size_t Id,
		unordered_set<string> &Names,
		unordered_set<size_t> &Children,
		unordered_set<string> &Added,
		unordered_set<string> &Removed,
		size_t Amount,
		float Ratio,
		float Changes,
		bool Removing
	);
}

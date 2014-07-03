#pragma once
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "helper/bar.h"
#include "helper/serialize.h"
***REMOVED***
***REMOVED***
/*
 * This namespace holds all code that connects to the database.
 */
namespace Queries {
	using namespace std;
***REMOVED***
	// Struct for the ratio rows
	struct Ratio {
		string parent, child;
		float parentratio, childratio;
	};
	Serialize &operator<<(Serialize &serialize, const Ratio &ratio);
	Deserialize &operator>>(Deserialize &deserialize, Ratio &ratio);
***REMOVED***
	// Struct for the field values
	struct Field {
		string name, roll, domain;
		size_t position;
		bool operator==(const Field &other) const { return name == other.name; }
	};
	Serialize &operator<<(Serialize &serialize, const Field &field);
	Deserialize &operator>>(Deserialize &deserialize, Field &field);
***REMOVED***
	// Implement a find function for the difference check
	struct find_field : unary_function<Field, bool> {
		string name;
		find_field(Field f) :name(f.name) { }
		bool operator()(Field const& f) const { return f.name == name; }
	};
***REMOVED***
	// Global connection details
	static string Dsn = "HANA";
	static string User = "***REMOVED***";
	static string Password = "***REMOVED***";
***REMOVED***
	// Fetching functions
	vector<Ratio> Ratios();
	vector<Field> Fields(string Table);
	vector<unordered_set<Field>> Structures(vector<string> &Names);
***REMOVED***
	// Inserting functions
	bool Store(size_t Id,
		unordered_map<size_t, float> &Ratios,
		unordered_set<string> &Names,
		unordered_set<size_t> &Children,
		size_t Amount,
		pair<unordered_set<string>, unordered_set<string>> &Differences);
}
***REMOVED***
// Type traits
namespace std {
	template <>
	struct hash<Queries::Field>
	{
		size_t operator()(const Queries::Field &f) const {
			using std::hash;
			return (hash<string>()(f.name)
				^ ((hash<string>()(f.roll)     << 1) >> 1)
				^ ((hash<string>()(f.domain)   << 1) >> 1)
				^ ((hash<size_t>()(f.position) << 1) >> 1));
		}
	};
}

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
	// Struct for the ratio rows
	struct Ratio {
		std::string parent, child;
		float parentratio, childratio;
	};
	Serialize &operator<<(Serialize &serialize, const Ratio &ratio);
	Deserialize &operator>>(Deserialize &deserialize, Ratio &ratio);
***REMOVED***
	// Struct for the field values
	struct Field {
		std::string name, roll, domain;
		size_t position;
		bool operator==(const Field &other) const
		{
			return name == other.name;
		}
	};
	Serialize &operator<<(Serialize &serialize, const Field &field);
	Deserialize &operator>>(Deserialize &deserialize, Field &field);
***REMOVED***
	// Implement a find function for the difference check
	struct find_field : std::unary_function<Field, bool> {
		std::string name;
		find_field(Field f) :name(f.name) { }
		bool operator()(Field const& f) const {
			return f.name == name;
		}
	};
***REMOVED***
	static std::string Dsn = "***REMOVED***";
	static std::string User = "***REMOVED***";
	static std::string Password = "***REMOVED***";
***REMOVED***
	std::vector<Ratio> Ratios();
	std::vector<Field> Fields(std::string Table);
	std::vector<std::unordered_set<Field>> Structures(std::unordered_map<std::string, size_t> &Ids);
}
***REMOVED***
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
